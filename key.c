#include "key.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

/*!
  \file
  \brief functions to create the key values
*/

 /*
  * ! \brief unions a key with the key value of a point
  */
static int32 *
key_add_point(int32 *key, const SPoint *p)
{
	static int32 k[3];

	spherepoint_gen_key(&k[0], p);
	spherekey_union_two(key, &k[0]);
	return key;
}

int32 *
spherekey_union_two(int32 *kunion, const int32 *key)
{
	kunion[0] = min(kunion[0], key[0]);
	kunion[1] = min(kunion[1], key[1]);
	kunion[2] = min(kunion[2], key[2]);
	kunion[3] = max(kunion[3], key[3]);
	kunion[4] = max(kunion[4], key[4]);
	kunion[5] = max(kunion[5], key[5]);
	return kunion;
}

int32 *
spherekey_inter_two(int32 *kinter, const int32 *key)
{
	if (kinter[3] < key[0] || key[3] < kinter[0])
		return NULL;
	if (kinter[4] < key[1] || key[4] < kinter[1])
		return NULL;
	if (kinter[5] < key[2] || key[5] < kinter[2])
		return NULL;
	kinter[0] = max(kinter[0], key[0]);
	kinter[1] = max(kinter[1], key[1]);
	kinter[2] = max(kinter[2], key[2]);
	kinter[3] = min(kinter[3], key[3]);
	kinter[4] = min(kinter[4], key[4]);
	kinter[5] = min(kinter[5], key[5]);
	return kinter;
}

int32 *
spherepoint_gen_key(int32 *k, const SPoint *sp)
{
	Vector3D	v;
	static const int32 ks = MAXCVALUE;

	spoint_vector3d(&v, sp);

	if (v.x < -1.0)
		v.x = -1.0;
	if (v.y < -1.0)
		v.y = -1.0;
	if (v.z < -1.0)
		v.z = -1.0;
	if (v.x > 1.0)
		v.x = 1.0;
	if (v.y > 1.0)
		v.y = 1.0;
	if (v.z > 1.0)
		v.z = 1.0;

	k[0] = v.x * ks;
	k[1] = v.y * ks;
	k[2] = v.z * ks;
	k[3] = v.x * ks;
	k[4] = v.y * ks;
	k[5] = v.z * ks;

	return (k);
}


int32 *
spherecircle_gen_key(int32 *k, const SCIRCLE *c)
{
	static double r,
				d;
	static const int32 ks = MAXCVALUE;
	static int	i;
	static Vector3D v[8];
	static Vector3D tv;
	static Vector3D mm[2];
	static SEuler se;

	r = sin(c->radius);
	d = cos(c->radius);

	v[0].x = -r;
	v[0].y = -r;
	v[0].z = d;
	v[1].x = -r;
	v[1].y = +r;
	v[1].z = d;
	v[2].x = +r;
	v[2].y = -r;
	v[2].z = d;
	v[3].x = +r;
	v[3].y = +r;
	v[3].z = d;
	v[4].x = -r;
	v[4].y = -r;
	v[4].z = 1.0;
	v[5].x = -r;
	v[5].y = +r;
	v[5].z = 1.0;
	v[6].x = +r;
	v[6].y = -r;
	v[6].z = 1.0;
	v[7].x = +r;
	v[7].y = +r;
	v[7].z = 1.0;

	se.psi_a = EULER_AXIS_X;
	se.theta_a = EULER_AXIS_Z;
	se.phi_a = EULER_AXIS_X;
	se.phi = PIH - c->center.lat;
	se.theta = PIH + c->center.lng;
	se.psi = 0.0;
	/* min */
	mm[0].x = mm[0].y = mm[0].z = 1.0;
	/* max */
	mm[1].x = mm[1].y = mm[1].z = -1.0;

	for (i = 0; i < 8; i++)
	{
		euler_vector_trans(&tv, &v[i], &se);
		if (tv.x >= -1.0 && tv.x <= 1.0)
		{
			mm[0].x = min(mm[0].x, tv.x);
			mm[1].x = max(mm[1].x, tv.x);
		}
		else if (tv.x < -1.0)
		{
			mm[0].x = -1.0;
		}
		else if (tv.x > 1.0)
		{
			mm[1].x = 1.0;
		}

		if (tv.y >= -1.0 && tv.y <= 1.0)
		{
			mm[0].y = min(mm[0].y, tv.y);
			mm[1].y = max(mm[1].y, tv.y);
		}
		else if (tv.y < -1.0)
		{
			mm[0].y = -1.0;
		}
		else if (tv.y > 1.0)
		{
			mm[1].y = 1.0;
		}

		if (tv.z >= -1.0 && tv.z <= 1.0)
		{
			mm[0].z = min(mm[0].z, tv.z);
			mm[1].z = max(mm[1].z, tv.z);
		}
		else if (tv.z < -1.0)
		{
			mm[0].z = -1.0;
		}
		else if (tv.z > 1.0)
		{
			mm[1].z = 1.0;
		}
	}

	k[0] = mm[0].x * ks;
	k[1] = mm[0].y * ks;
	k[2] = mm[0].z * ks;
	k[3] = mm[1].x * ks;
	k[4] = mm[1].y * ks;
	k[5] = mm[1].z * ks;

	return (k);

}


int32 *
sphereellipse_gen_key(int32 *k, const SELLIPSE *e)
{
	static double r[2],
				d;
	static const int32 ks = MAXCVALUE;
	static int	i;
	static Vector3D v[8];
	static Vector3D tv;
	static Vector3D mm[2];
	static SEuler se;

	r[0] = sin(e->rad[0]);
	r[1] = sin(e->rad[1]);
	d = cos(e->rad[1]);

	v[0].x = d;
	v[0].y = -r[0];
	v[0].z = -r[1];
	v[1].x = d;
	v[1].y = +r[0];
	v[1].z = -r[1];
	v[2].x = d;
	v[2].y = -r[0];
	v[2].z = +r[1];
	v[3].x = d;
	v[3].y = +r[0];
	v[3].z = +r[1];
	v[4].x = 1.0;
	v[4].y = -r[0];
	v[4].z = -r[1];
	v[5].x = 1.0;
	v[5].y = +r[0];
	v[5].z = -r[1];
	v[6].x = 1.0;
	v[6].y = -r[0];
	v[6].z = +r[1];
	v[7].x = 1.0;
	v[7].y = +r[0];
	v[7].z = +r[1];

	sellipse_trans(&se, e);

	/* min */
	mm[0].x = mm[0].y = mm[0].z = 1.0;
	/* max */
	mm[1].x = mm[1].y = mm[1].z = -1.0;

	for (i = 0; i < 8; i++)
	{
		euler_vector_trans(&tv, &v[i], &se);
		if (tv.x >= -1.0 && tv.x <= 1.0)
		{
			mm[0].x = min(mm[0].x, tv.x);
			mm[1].x = max(mm[1].x, tv.x);
		}
		else if (tv.x < -1.0)
		{
			mm[0].x = -1.0;
		}
		else if (tv.x > 1.0)
		{
			mm[1].x = 1.0;
		}

		if (tv.y >= -1.0 && tv.y <= 1.0)
		{
			mm[0].y = min(mm[0].y, tv.y);
			mm[1].y = max(mm[1].y, tv.y);
		}
		else if (tv.y < -1.0)
		{
			mm[0].y = -1.0;
		}
		else if (tv.y > 1.0)
		{
			mm[1].y = 1.0;
		}

		if (tv.z >= -1.0 && tv.z <= 1.0)
		{
			mm[0].z = min(mm[0].z, tv.z);
			mm[1].z = max(mm[1].z, tv.z);
		}
		else if (tv.z < -1.0)
		{
			mm[0].z = -1.0;
		}
		else if (tv.z > 1.0)
		{
			mm[1].z = 1.0;
		}


	}
	k[0] = mm[0].x * ks;
	k[1] = mm[0].y * ks;
	k[2] = mm[0].z * ks;
	k[3] = mm[1].x * ks;
	k[4] = mm[1].y * ks;
	k[5] = mm[1].z * ks;

	return (k);
}


int32 *
sphereline_gen_key(int32 *k, const SLine *sl)
{
	static const int32 ks = MAXCVALUE;
	static SPoint p[3];

	sline_begin(&p[0], sl);
	sline_end(&p[1], sl);

	if (FPzero(sl->length))
	{

		static Vector3D vbeg,
					vend;

		spoint_vector3d(&vbeg, &p[0]);
		spoint_vector3d(&vend, &p[1]);

		k[0] = min(vbeg.x, vend.x) * ks;
		k[1] = min(vbeg.y, vend.y) * ks;
		k[2] = min(vbeg.z, vend.z) * ks;
		k[3] = max(vbeg.x, vend.x) * ks;
		k[4] = max(vbeg.y, vend.y) * ks;
		k[5] = max(vbeg.z, vend.z) * ks;

	}
	else
	{

		static Vector3D v[4],
					vt,
					vr[2];
		static SEuler se;
		static float8 l,
					ls,
					lc;
		static int8 i;

		sphereline_to_euler(&se, sl);
		l = sl->length / 2.0;
		ls = sin(l);
		lc = cos(l);
		se.phi += l;

		v[0].x = lc;
		v[0].y = ((lc < 0) ? (-1.0) : (-ls));
		v[1].x = 1.0;
		v[1].y = ((lc < 0) ? (-1.0) : (-ls));
		v[2].x = lc;
		v[2].y = ((lc < 0) ? (+1.0) : (+ls));
		v[3].x = 1.0;
		v[3].y = ((lc < 0) ? (+1.0) : (+ls));
		v[0].z = v[1].z = v[2].z = v[3].z = 0.0;

		vr[0].x = vr[0].y = vr[0].z = 1.0;
		vr[1].x = vr[1].y = vr[1].z = -1.0;

		for (i = 0; i < 4; i++)
		{
			euler_vector_trans(&vt, &v[i], &se);
			if (vt.x >= -1.0 && vt.x <= 1.0)
			{
				vr[0].x = min(vr[0].x, vt.x);
				vr[1].x = max(vr[1].x, vt.x);
			}
			if (vt.y >= -1.0 && vt.y <= 1.0)
			{
				vr[0].y = min(vr[0].y, vt.y);
				vr[1].y = max(vr[1].y, vt.y);
			}
			if (vt.z >= -1.0 && vt.z <= 1.0)
			{
				vr[0].z = min(vr[0].z, vt.z);
				vr[1].z = max(vr[1].z, vt.z);
			}
		}

		k[0] = vr[0].x * ks;
		k[1] = vr[0].y * ks;
		k[2] = vr[0].z * ks;
		k[3] = vr[1].x * ks;
		k[4] = vr[1].y * ks;
		k[5] = vr[1].z * ks;

	}

	return k;
}

 /*
  * ! \brief Creates the key of a polygon \param sp pointer to polygon \param
  * key pointer to key \return pointer to key
  */

int32 *
spherepoly_gen_key(int32 *key, const SPOLY *sp)
{
	static int32 i;
	static SLine l;
	static int32 tk[6];
	bool		start = TRUE;

	for (i = 0; i < sp->npts; i++)
	{
		sline_from_points(&l, &sp->p[i], &sp->p[(i + 1) % sp->npts]);
		sphereline_gen_key(&tk[0], &l);
		if (start)
		{
			start = FALSE;
			memcpy((void *) key, (void *) &tk[0], KEYSIZE);
		}
		else
		{
			key[0] = min(key[0], tk[0]);
			key[1] = min(key[1], tk[1]);
			key[2] = min(key[2], tk[2]);
			key[3] = max(key[3], tk[3]);
			key[4] = max(key[4], tk[4]);
			key[5] = max(key[5], tk[5]);
		}
	}

	return key;
}


int32 *
spherepath_gen_key(int32 *key, const SPATH *sp)
{
	static int32 i,
				k,
				r;
	static SLine l;
	static int32 tk[6];
	bool		start = TRUE;

	for (i = 0; i < sp->npts; i++)
	{
		for (k = i + 1; i < sp->npts; i++)
		{
			r = ((k == sp->npts) ? (0) : (k));
			sline_from_points(&l, &sp->p[i], &sp->p[r]);
			sphereline_gen_key(&tk[0], &l);
			if (start)
			{
				start = FALSE;
				memcpy((void *) key, (void *) &tk[0], KEYSIZE);
			}
			else
			{
				key[0] = min(key[0], tk[0]);
				key[1] = min(key[1], tk[1]);
				key[2] = min(key[2], tk[2]);
				key[3] = max(key[3], tk[3]);
				key[4] = max(key[4], tk[4]);
				key[5] = max(key[5], tk[5]);
			}
		}
	}

	return key;
}



int32 *
spherebox_gen_key(int32 *key, const SBOX *box)
{
	static SPoint p;
	static float8 d;

	key[0] = key[1] = key[2] = MAXCVALUE;
	key[3] = key[4] = key[5] = -MAXCVALUE;

	/* add the 4 edges */
	key_add_point(key, &box->sw);
	key_add_point(key, &box->ne);
	p.lng = box->sw.lng;
	p.lat = box->ne.lat;
	key_add_point(key, &p);
	p.lng = box->ne.lng;
	p.lat = box->sw.lat;
	key_add_point(key, &p);

	/* latitude closest to equator */
	if (FPge(box->ne.lat, 0.0) && FPle(box->sw.lat, 0.0))
	{
		p.lat = 0.0;
	}
	else if (fabs(box->ne.lat) > fabs(box->sw.lat))
	{
		p.lat = box->sw.lat;
	}
	else
	{
		p.lat = box->ne.lat;
	}

	for (d = 0.0; d < (PID - 0.1); d += PIH)
	{
		p.lng = d;
		if (sbox_cont_point(box, &p))
		{
			key_add_point(key, &p);
		}
	}

	return key;
}
