;; collin gros
;; 11-18-2020
;; cs471
;; lisp
;;
;; FOR THIS ASSIGNMENT: we don't check for correctness, and we assume
;; 						that we are given a CD beforehand.
;; (code from lecture by Shaun Cooper)
;; tells you how many of an element, x, are in a list, L,
;; including nested lists
;;
;; example i/o:
;;	i: `a `(a b (c a d))
;;	o: 2
;;

(define (howmany x L)
	(cond	((null? L) 0)
			((not (list? L))
				(if (eq? x L) 1 0))
				;; if atom is x, 1 otherwise 0
				(else (+ (howmany x (car L))
						;; count of x in head of list
						(howmany x (cdr L))))))
						;; count of x in remainder of list

