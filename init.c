#include "postgres.h"
#include "optimizer/paths.h"
#include "optimizer/restrictinfo.h"
#include "utils/builtins.h"
#include "utils/elog.h"
#include "utils/lsyscache.h"
#include "nodes/print.h"
#include "catalog/pg_proc.h"
#include "catalog/pg_operator.h"
#include "commands/explain.h"
#include "funcapi.h"

extern void _PG_init(void);

static set_join_pathlist_hook_type set_join_pathlist_next;

typedef struct
{
	CustomPath		cpath;

	JoinType		jointype;

	Path		   *outer_path;
	Path		   *inner_path;

	List		   *joinrestrictinfo;
} CrossmatchJoinPath;

static CustomPathMethods	crossmatch_path_methods;
static CustomScanMethods	crossmatch_plan_methods;
static CustomExecMethods	crossmatch_exec_methods;

void join_pathlist_hook (PlannerInfo *root,
						 RelOptInfo *joinrel,
						 RelOptInfo *outerrel,
						 RelOptInfo *innerrel,
						 JoinType jointype,
						 JoinPathExtraData *extra)
{
	ListCell   *restr;
	text	   *dist_func_name = cstring_to_text("dist(spoint,spoint)");
	Oid			dist_func;

	dist_func = DatumGetObjectId(DirectFunctionCall1(to_regprocedure,
													 PointerGetDatum(dist_func_name)));

	if (dist_func == InvalidOid)
		elog(ERROR, "function dist not found!");

	if (set_join_pathlist_next)
		set_join_pathlist_next(root,
							   joinrel,
							   outerrel,
							   innerrel,
							   jointype,
							   extra);

	foreach(restr, extra->restrictlist)
	{
		RestrictInfo *restrInfo = (RestrictInfo *) lfirst(restr);

		if (IsA(restrInfo->clause, OpExpr))
		{
			OpExpr	   *opExpr = (OpExpr *) restrInfo->clause;
			int			nargs = list_length(opExpr->args);
			Node	   *arg1;
			Node	   *arg2;

			if (nargs != 2)
				continue;

			arg1 = linitial(opExpr->args);
			arg2 = lsecond(opExpr->args);

			if (opExpr->opno == Float8LessOperator &&
				IsA(arg1, FuncExpr) &&
				((FuncExpr *) arg1)->funcid == dist_func &&
				IsA(arg2, Const))
			{
				elog(LOG, "found <");
			}
			else if (opExpr->opno == get_commutator(Float8LessOperator) &&
					 IsA(arg1, Const) &&
					 IsA(arg2, FuncExpr) &&
					 ((FuncExpr *) arg2)->funcid == dist_func)
			{
				elog(LOG, "found >");
			}
		}
	}

	pprint(root->parse->rtable);
}

static CrossmatchJoinPath *
create_crossmatch_path(PlannerInfo *root,
					   RelOptInfo *joinrel,
					   Path *outer_path,
					   Path *inner_path,
					   ParamPathInfo *param_info,
					   List *restrict_clauses,
					   Relids required_outer)
{
	CrossmatchJoinPath *result;

	result = palloc0(sizeof(CrossmatchJoinPath));
	NodeSetTag(result, T_CustomPath);

	result->cpath.path.pathtype = T_CustomScan;
	result->cpath.path.parent = joinrel;
	result->cpath.path.param_info = param_info;
	result->cpath.path.pathkeys = NIL;
	result->cpath.path.rows = joinrel->rows;
	result->cpath.flags = 0;
	result->cpath.methods = &crossmatch_path_methods;
	result->outer_path = outer_path;
	result->inner_path = inner_path;
	result->joinrestrictinfo = restrict_clauses;

	/* DEBUG costs */
	result->cpath.path.startup_cost = 1;
	result->cpath.path.total_cost = 1;

	return result;
}

static Plan *
create_crossmatch_plan(PlannerInfo *root,
					   RelOptInfo *rel,
					   CustomPath *best_path,
					   List *tlist,
					   List *clauses,
					   List *custom_plans)
{
	CrossmatchJoinPath	   *gpath = (CrossmatchJoinPath *) best_path;
	List				   *joinrestrictclauses = gpath->joinrestrictinfo;
	List				   *joinclauses;
	List				   *otherclauses;
	CustomScan			   *cscan;

	if (IS_OUTER_JOIN(gpath->jointype))
	{
		extract_actual_join_clauses(joinrestrictclauses,
									&joinclauses, &otherclauses);
	}
	else
	{
		joinclauses = extract_actual_clauses(joinrestrictclauses,
											 false);
		otherclauses = NIL;
	}

	cscan = makeNode(CustomScan);
	cscan->scan.plan.targetlist = tlist;
	cscan->scan.plan.qual = NIL;

	cscan->flags = best_path->flags;
	cscan->methods = &crossmatch_plan_methods;
	cscan->custom_plans = list_copy_tail(custom_plans, 1);


}

static Node *
crossmatch_create_scan_state(CustomScan *node)
{
	return NULL;
}

static void
crossmatch_begin(CustomScanState *node, EState *estate, int eflags)
{

}

static TupleTableSlot *
crossmatch_exec(CustomScanState *node)
{
	return NULL;
}

static void
crossmatch_end(CustomScanState *node)
{

}

static void
crossmatch_rescan(CustomScanState *node)
{

}

static void
crossmatch_explain(CustomScanState *node, List *ancestors, ExplainState *es)
{

}

void
_PG_init(void)
{
	elog(LOG, "loading pg_sphere");

	set_join_pathlist_next = set_join_pathlist_hook;
	set_join_pathlist_hook = join_pathlist_hook;

	crossmatch_path_methods.CustomName				= "CrossmatchJoin";
	crossmatch_path_methods.PlanCustomPath			= &create_crossmatch_plan;

	crossmatch_plan_methods.CustomName 				= "CrossmatchJoin";
	crossmatch_plan_methods.CreateCustomScanState	= &crossmatch_create_scan_state;

	crossmatch_exec_methods.CustomName				= "CrossmatchJoin";
	crossmatch_exec_methods.BeginCustomScan			= &crossmatch_begin;
	crossmatch_exec_methods.ExecCustomScan			= &crossmatch_exec;
	crossmatch_exec_methods.EndCustomScan			= &crossmatch_end;
	crossmatch_exec_methods.ReScanCustomScan		= &crossmatch_rescan;
	crossmatch_exec_methods.MarkPosCustomScan		= NULL;
	crossmatch_exec_methods.RestrPosCustomScan		= NULL;
	crossmatch_exec_methods.ExplainCustomScan		= &crossmatch_explain;
}