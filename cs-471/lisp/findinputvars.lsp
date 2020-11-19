;; collin gros
;; 11-18-2020
;; cs471
;; lisp
;;
;; findinputvars - clean up all other stuff in a CD
;; modified version of Shaun Cooper's code from lecture
;;
;; WE GET A FLATTENED UNIQ CD
;;

(define (findinputvars L)
	(cond ((null? L) `())
		;; if list is null return ()
		((not (list? L)) `())
		;; if list is an atom return ()
		((or (eq? (car L) 1)
			 (eq? (car L) 0)
			 (eq? (car L) `AND)
			 (eq? (car L) `OR)
			 (eq? (car L) `NOT))
			;; we want to ignore all of these so we want to examine the
			;; rest of the list
			(findinputvars (cdr L)))
		(else (cons (car L) (findinputvars (cdr L))))))

