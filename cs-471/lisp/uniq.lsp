;; collin gros
;; 11-18-2020
;; cs471
;; lisp
;;
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



