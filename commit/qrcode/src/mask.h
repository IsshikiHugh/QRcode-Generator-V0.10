#pragma once

matrix extract_base( matrix m );

matrix make_mask( matrix m , int mode );

int score_mask( matrix mask , matrix qrcode );
