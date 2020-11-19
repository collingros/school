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
;; pre: takes a list L
;; post: returns all input VARIABLES in L
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


;; uniq - extracts unique atoms from a FLATTENED list or nested lists
;;				---note: THE LIST MUST BE FLATTENED
;;
;; (used some modified Shaun Cooper's code from lecture)
;; pre: takes a list L
;; post: returns uniq elements in list L
(define (uniq L)
	(cond	((null? L) `())
			;; uniq of empty list is empty list
			((not (list? L)) `())
			;; uniq of junk is empty list (given is not a list)
			((member (car L) (cdr L)) (uniq (cdr L)))
			;; if car L is in the rest of the list, we can ignore car L
			(else (cons (car L) (uniq (cdr L))))))
			;; if not, we need to add this element to the uniq of the
			;; rest of the list
			;;
			;; e.g., (a b c) == (cons `a (uniq `(b c))
			;;						(cons `b (uniq `(c)))
			;;							(cons `c (uniq `()))
			;;								`()

