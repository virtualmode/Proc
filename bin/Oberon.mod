MODULE Debug;

(* IMPORT Out; Пример. *)

VAR
    matrix  : ARRAY 3 OF ARRAY 3 OF INTEGER;
    i, j, k : INTEGER;

BEGIN

    (* WHILE example *)
    i := 0;
    WHILE i < 10 DO
        IF (i = 0) THEN
            i := 1;
        ELSIF (i = 1) THEN
            i := 2;
        ELSE
            i := i + 1;
        END;
    END;

    i := 1;
    j := 2;
    k := i + j * 2;

END Debug.
