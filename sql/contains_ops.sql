
-- scircle vs spoint
select 'scircle @> spoint', 't' as expected, scircle(spoint(1.0,1.0),0.1) @> spoint(1.0,1.0) as actual;
select 'scircle @> spoint', 'f' as expected, scircle(spoint(1.0,1.0),0.1) @> spoint(2.0,2.0) as actual;

select 'spoint <@ scircle', 't' as expected, spoint(1.0,1.0) <@ scircle(spoint(1.0,1.0),0.1) as actual;
select 'spoint <@ scircle', 'f' as expected, spoint(2.0,2.0) <@ scircle(spoint(1.0,1.0),0.1) as actual;

select 'scircle !@> spoint', 'f' as expected, scircle(spoint(1.0,1.0),0.1) !@> spoint(1.0,1.0) as actual;
select 'scircle !@> spoint', 't' as expected, scircle(spoint(1.0,1.0),0.1) !@> spoint(2.0,2.0) as actual;

select 'spoint !<@ scircle', 'f' as expected, spoint(1.0,1.0) !<@ scircle(spoint(1.0,1.0),0.1) as actual;
select 'spoint !<@ scircle', 't' as expected, spoint(2.0,2.0) !<@ scircle(spoint(1.0,1.0),0.1) as actual;

-- sbox vs spoint
select 'sbox @> spoint', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) @> spoint(1.1,1.1) as actual;
select 'sbox @> spoint', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) @> spoint(2.0,2.0) as actual;

select 'spoint <@ sbox', 't' as expected, spoint(1.1,1.1) <@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'spoint <@ sbox', 'f' as expected, spoint(2.0,2.0) <@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;

select 'sbox !@> spoint', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !@> spoint(1.1,1.1) as actual;
select 'sbox !@> spoint', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !@> spoint(2.0,2.0) as actual;

select 'spoint !<@ sbox', 'f' as expected, spoint(1.1,1.1) !<@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'spoint !<@ sbox', 't' as expected, spoint(2.0,2.0) !<@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;

-- spoly vs spoint
select 'spoly @> spoint', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly @> spoint(1.1,1.1) as actual;
select 'spoly @> spoint', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly @> spoint(2.0,2.0) as actual;

select 'spoint <@ spoly', 't' as expected, spoint(1.1,1.1) <@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'spoint <@ spoly', 'f' as expected, spoint(2.0,2.0) <@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;

select 'spoly !@> spoint', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !@> spoint(1.1,1.1) as actual;
select 'spoly !@> spoint', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !@> spoint(2.0,2.0) as actual;

select 'spoint !<@ spoly', 'f' as expected, spoint(1.1,1.1) !<@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'spoint !<@ spoly', 't' as expected, spoint(2.0,2.0) !<@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;

-- scircle vs scircle
select 'scircle @> scircle', 't' as expected, scircle(spoint(1.0,1.0),0.1) @> scircle(spoint(1.0,1.0),0.05) as actual;
select 'scircle @> scircle', 'f' as expected, scircle(spoint(1.0,1.0),0.1) @> scircle(spoint(2.0,2.0),0.05) as actual;
select 'scircle @> scircle', 'f' as expected, scircle(spoint(1.0,1.0),0.1) @> scircle(spoint(1.0,1.0),0.2) as actual;

select 'scircle <@ scircle', 't' as expected, scircle(spoint(1.0,1.0),0.05) <@ scircle(spoint(1.0,1.0),0.1) as actual;
select 'scircle <@ scircle', 'f' as expected, scircle(spoint(2.0,2.0),0.05) <@ scircle(spoint(1.0,1.0),0.1) as actual;
select 'scircle <@ scircle', 'f' as expected, scircle(spoint(1.0,1.0),0.2) <@ scircle(spoint(1.0,1.0),0.1) as actual;

select 'scircle !@> scircle', 'f' as expected, scircle(spoint(1.0,1.0),0.1) !@> scircle(spoint(1.0,1.0),0.05) as actual;
select 'scircle !@> scircle', 't' as expected, scircle(spoint(1.0,1.0),0.1) !@> scircle(spoint(2.0,2.0),0.05) as actual;
select 'scircle !@> scircle', 't' as expected, scircle(spoint(1.0,1.0),0.1) !@> scircle(spoint(1.0,1.0),0.2) as actual;

select 'scircle !<@ scircle', 'f' as expected, scircle(spoint(1.0,1.0),0.05) !<@ scircle(spoint(1.0,1.0),0.1) as actual;
select 'scircle !<@ scircle', 't' as expected, scircle(spoint(2.0,2.0),0.05) !<@ scircle(spoint(1.0,1.0),0.1) as actual;
select 'scircle !<@ scircle', 't' as expected, scircle(spoint(1.0,1.0),0.2) !<@ scircle(spoint(1.0,1.0),0.1) as actual;

-- sbox vs scircle
select 'sbox @> scircle', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) @> scircle(spoint(1.1,1.1),0.01) as actual;
select 'sbox @> scircle', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) @> scircle(spoint(2.0,2.0),0.01) as actual;
select 'sbox @> scircle', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) @> scircle(spoint(1.1,1.1),0.2) as actual;

select 'scircle <@ sbox', 't' as expected, scircle(spoint(1.1,1.1),0.01) <@  sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle <@ sbox', 'f' as expected, scircle(spoint(2.0,2.0),0.01) <@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle <@ sbox', 'f' as expected, scircle(spoint(1.1,1.1),0.2) <@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;

select 'sbox !@> scircle', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !@> scircle(spoint(1.1,1.1),0.01) as actual;
select 'sbox !@> scircle', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !@> scircle(spoint(2.0,2.0),0.01) as actual;
select 'sbox !@> scircle', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !@> scircle(spoint(1.1,1.1),0.2) as actual;

select 'scircle !<@ sbox', 'f' as expected, scircle(spoint(1.1,1.1),0.01) !<@  sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle !<@ sbox', 't' as expected, scircle(spoint(2.0,2.0),0.01) !<@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle !<@ sbox', 't' as expected, scircle(spoint(1.1,1.1),0.2) !<@ sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
--
select 'scircle @> sbox', 't' as expected, scircle(spoint(1.1,1.1),0.2) @>  sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle @> sbox', 'f' as expected, scircle(spoint(2.0,2.0),0.2) @> sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle @> sbox', 'f' as expected, scircle(spoint(1.1,1.1),0.01) @> sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;

select 'sbox <@ scircle', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) <@ scircle(spoint(1.1,1.1),0.2) as actual;
select 'sbox <@ scircle', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) <@ scircle(spoint(2.0,2.0),0.2) as actual;
select 'sbox <@ scircle', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) <@ scircle(spoint(1.1,1.1),0.01) as actual;

select 'scircle !@> sbox', 'f' as expected, scircle(spoint(1.1,1.1),0.2) !@>  sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle !@> sbox', 't' as expected, scircle(spoint(2.0,2.0),0.2) !@> sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;
select 'scircle !@> sbox', 't' as expected, scircle(spoint(1.1,1.1),0.01) !@> sbox(spoint(1.0,1.0),spoint(1.2,1.2)) as actual;

select 'sbox !<@ scircle', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !<@ scircle(spoint(1.1,1.1),0.2) as actual;
select 'sbox !<@ scircle', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !<@ scircle(spoint(2.0,2.0),0.2) as actual;
select 'sbox !<@ scircle', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.2,1.2)) !<@ scircle(spoint(1.1,1.1),0.01) as actual;

-- spoly vs scircle
select 'spoly @> scircle', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly @> scircle(spoint(1.1,1.1),0.01) as actual;
select 'spoly @> scircle', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly @> scircle(spoint(2.0,2.0),0.2) as actual;
select 'spoly @> scircle', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly @> scircle(spoint(1.1,1.1),0.2) as actual;

select 'scircle <@ spoly', 't' as expected, scircle(spoint(1.1,1.1),0.01) <@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle <@ spoly', 'f' as expected, scircle(spoint(2.0,2.0),0.01) <@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle <@ spoly', 'f' as expected, scircle(spoint(1.1,1.1),0.2) <@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;

select 'spoly !@> scircle', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !@> scircle(spoint(1.1,1.1),0.01) as actual;
select 'spoly !@> scircle', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !@> scircle(spoint(2.0,2.0),0.2) as actual;
select 'spoly !@> scircle', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !@> scircle(spoint(1.1,1.1),0.2) as actual;

select 'scircle !<@ spoly', 'f' as expected, scircle(spoint(1.1,1.1),0.01) !<@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle !<@ spoly', 't' as expected, scircle(spoint(2.0,2.0),0.01) !<@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle !<@ spoly', 't' as expected, scircle(spoint(1.1,1.1),0.2) !<@ '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
--
select 'scircle @> spoly', 't' as expected, scircle(spoint(1.1,1.1),0.5) @> '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle @> spoly', 'f' as expected, scircle(spoint(2.0,2.0),0.5) @> '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle @> spoly', 'f' as expected, scircle(spoint(1.1,1.1),0.05) @> '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;

select 'spoly <@ scircle', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly <@ scircle(spoint(1.1,1.1),0.5) as actual;
select 'spoly <@ scircle', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly <@ scircle(spoint(2.0,2.0),0.5) as actual;
select 'spoly <@ scircle', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly <@ scircle(spoint(1.1,1.1),0.05) as actual;

select 'scircle !@> spoly', 'f' as expected, scircle(spoint(1.1,1.1),0.5) !@> '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle !@> spoly', 't' as expected, scircle(spoint(2.0,2.0),0.5) !@> '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;
select 'scircle !@> spoly', 't' as expected, scircle(spoint(1.1,1.1),0.05) !@> '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly as actual;

select 'spoly !<@ scircle', 'f' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !<@ scircle(spoint(1.1,1.1),0.5) as actual;
select 'spoly !<@ scircle', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !<@ scircle(spoint(2.0,2.0),0.5) as actual;
select 'spoly !<@ scircle', 't' as expected, '{(1.0,1.0),(1.2,1.0),(1.2,1.2),(1.0,1.2)}'::spoly !<@ scircle(spoint(1.1,1.1),0.05) as actual;


-- sbox vs spoly
select 'sbox @> spoly', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.5,1.5)) @> '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;
select 'sbox @> spoly', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.5,1.5)) @> '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly as actual;
select 'sbox @> spoly', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.5,1.5)) @> '{(0.9 , 0.9),(1.1 , 0.9),(1.1 , 1.1),(0.9 , 1.1)}'::spoly as actual;

select 'spoly <@ sbox', 't' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly <@ sbox(spoint(1.0,1.0),spoint(1.5,1.5)) as actual;
select 'spoly <@ sbox', 'f' as expected, '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly <@  sbox(spoint(1.0,1.0),spoint(1.5,1.5)) as actual;
select 'spoly <@ sbox', 'f' as expected, '{(0.9 , 0.9),(1.1 , 0.9),(1.1 , 1.1),(0.9 , 1.1)}'::spoly <@ sbox(spoint(1.0,1.0),spoint(1.5,1.5)) as actual;

select 'sbox !@> spoly', 'f' as expected, sbox(spoint(1.0,1.0),spoint(1.5,1.5)) !@> '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;
select 'sbox !@> spoly', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.5,1.5)) !@> '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly as actual;
select 'sbox !@> spoly', 't' as expected, sbox(spoint(1.0,1.0),spoint(1.5,1.5)) !@> '{(0.9,0.9),(1.1,0.9),(1.1,1.1),(0.9,1.1)}'::spoly as actual;

select 'spoly !<@ sbox', 'f' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly !<@ sbox(spoint(1.0,1.0),spoint(1.5,1.5)) as actual;
select 'spoly !<@ sbox', 't' as expected, '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly !<@  sbox(spoint(1.0,1.0),spoint(1.5,1.5)) as actual;
select 'spoly !<@ sbox', 't' as expected, '{(0.9 , 0.9),(1.1 , 0.9),(1.1 , 1.1),(0.9 , 1.1)}'::spoly !<@ sbox(spoint(1.0,1.0),spoint(1.5,1.5)) as actual;


-- spoly vs spoly
select 'spoly @> spoly', 't' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly @> '{(1.11,1.11),(1.19,1.11),(1.19,1.19),(1.11,1.19)}'::spoly as actual;
select 'spoly @> spoly', 'f' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly @> '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly as actual;
select 'spoly @> spoly', 'f' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly @> '{(0.9,0.9),(1.2,0.9),(1.2,1.2),(0.9,1.2)}'::spoly as actual;

select 'spoly <@ spoly', 't' as expected, '{(1.11,1.11),(1.19,1.11),(1.19,1.19),(1.11,1.19)}'::spoly <@ '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;
select 'spoly <@ spoly', 'f' as expected, '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly <@ '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;
select 'spoly <@ spoly', 'f' as expected, '{(0.9,0.9),(1.2,0.9),(1.2,1.2),(0.9,1.2)}'::spoly <@ '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;

select 'spoly !@> spoly', 'f' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly !@> '{(1.11,1.11),(1.19,1.11),(1.19,1.19),(1.11,1.19)}'::spoly as actual;
select 'spoly !@> spoly', 't' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly !@> '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly as actual;
select 'spoly !@> spoly', 't' as expected, '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly !@> '{(0.9,0.9),(1.2,0.9),(1.2,1.2),(0.9,1.2)}'::spoly as actual;

select 'spoly !<@ spoly', 'f' as expected, '{(1.11,1.11),(1.19,1.11),(1.19,1.19),(1.11,1.19)}'::spoly !<@ '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;
select 'spoly !<@ spoly', 't' as expected, '{(2.1,2.1),(2.2,1.1),(2.2,1.2),(2.1,1.2)}'::spoly !<@ '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;
select 'spoly !<@ spoly', 't' as expected, '{(0.9,0.9),(1.2,0.9),(1.2,1.2),(0.9,1.2)}'::spoly !<@ '{(1.1,1.1),(1.2,1.1),(1.2,1.2),(1.1,1.2)}'::spoly as actual;
