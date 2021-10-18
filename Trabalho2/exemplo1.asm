;Exemplo 1
;Calcula a area de um triangulo: OUTPUT R=(B*H)/2
;12 15 12 16 10 15 3 16 4 18 11 17 13 17 14 0 0 0 2

SECTION TEXT        ; comentario w djfksfk
INPUT B
INPUT H
LOAD B
MUL H
DIV DOIS
STORE R
OUTPUT R
STOP

SECTION DATA
B: SPACE            ;15
H: SPACE            ;16
R: SPACE            ;17
DOIS: CONST 2       ;18