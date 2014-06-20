-- indexed operations.....

SET enable_indexscan=off;

select count(sp) from spoint_data where sp @ '<(0d,90d),1.0d>'::scircle;

select count(sp) from spoint_data where '<(0d,90d),1.0d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,90d),1.1d>'::scircle;

select count(sp) from spoint_data where '<(0d,90d),1.1d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,-90d),1.0d>'::scircle;

select count(sp) from spoint_data where '<(0d,-90d),1.0d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,-90d),1.1d>'::scircle;

select count(sp) from spoint_data where '<(0d,-90d),1.1d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,0d),2.1d>'::scircle;

select count(sp) from spoint_data where '<(0d,0d),2.1d>'::scircle ~ sp;



select count(sc) from scircle_data where sc && '<(0d,90d),1.0d>';

select count(sc) from scircle_data where sc @ '<(0d,90d),1.0d>';

select count(sc) from scircle_data where '<(0d,90d),1.0d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,90d),1.1d>';

select count(sc) from scircle_data where sc @ '<(0d,90d),1.1d>';

select count(sc) from scircle_data where '<(0d,90d),1.1d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,-90d),1.0d>';

select count(sc) from scircle_data where sc @ '<(0d,-90d),1.0d>';

select count(sc) from scircle_data where '<(0d,-90d),1.0d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,-90d),1.1d>';

select count(sc) from scircle_data where sc @ '<(0d,-90d),1.1d>';

select count(sc) from scircle_data where '<(0d,-90d),1.1d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,0d),2.1d>'::scircle;

select count(sc) from scircle_data where sc @ '<(0d,0d),2.1d>'::scircle;

select count(sc) from scircle_data where '<(0d,0d),2.1d>'::scircle ~ sc;



SET enable_indexscan=on;

select count(sp) from spoint_data where sp @ '<(0d,90d),1.0d>'::scircle;

select count(sp) from spoint_data where '<(0d,90d),1.0d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,90d),1.1d>'::scircle;

select count(sp) from spoint_data where '<(0d,90d),1.1d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,-90d),1.0d>'::scircle;

select count(sp) from spoint_data where '<(0d,-90d),1.0d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,-90d),1.1d>'::scircle;

select count(sp) from spoint_data where '<(0d,-90d),1.1d>'::scircle ~ sp;

select count(sp) from spoint_data where sp @ '<(0d,0d),2.1d>'::scircle;

select count(sp) from spoint_data where '<(0d,0d),2.1d>'::scircle ~ sp;



select count(sc) from scircle_data where sc && '<(0d,90d),1.0d>';

select count(sc) from scircle_data where sc @ '<(0d,90d),1.0d>';

select count(sc) from scircle_data where '<(0d,90d),1.0d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,90d),1.1d>';

select count(sc) from scircle_data where sc @ '<(0d,90d),1.1d>';

select count(sc) from scircle_data where '<(0d,90d),1.1d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,-90d),1.0d>';

select count(sc) from scircle_data where sc @ '<(0d,-90d),1.0d>';

select count(sc) from scircle_data where '<(0d,-90d),1.0d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,-90d),1.1d>';

select count(sc) from scircle_data where sc @ '<(0d,-90d),1.1d>';

select count(sc) from scircle_data where '<(0d,-90d),1.1d>' ~ sc;

select count(sc) from scircle_data where sc && '<(0d,0d),2.1d>'::scircle;

select count(sc) from scircle_data where sc @ '<(0d,0d),2.1d>'::scircle;

select count(sc) from scircle_data where '<(0d,0d),2.1d>'::scircle ~ sc;


-- "Cross-correlation" about 30 seconds on PIII-750
select count(spoint_data.sp) from spoint_data,scircle_data where spoint_data.sp @ scircle_data.sc;
