BEGIN {
  do_print=1;
}
{
  if( match($0,"^--ifversion") ){  
    if( $2 == "<" && pg_version < $3 ){
      do_print = 1; next;
    } else
    if( $2 == "<=" && pg_version <= $3 ){
      do_print = 1; next;
    } else
    if( $2 == ">" && pg_version > $3 ){
      do_print = 1; next;
    } else
    if( $2 == ">=" && pg_version >= $3 ){
      do_print = 1; next;
    } else {
      do_print = 0; next;
    }
  } else
  if( match($0,"^--elseversion") ){
    do_print = 1 - do_print; next;
  } else  
  if( match($0,"^--endifversion") ){
    do_print = 1;next;
  }
  if( do_print ){
    print $0;
  }
}
