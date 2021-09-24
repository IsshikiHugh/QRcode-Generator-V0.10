#pragma once

matrix extract_base( matrix m );

matrix make_mask( matrix m , int mode );

matrix apply_mask( matrix output , matrix mask );

int evaluate( matrix m );
