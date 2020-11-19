;; collin gros
;; 11-18-2020
;; cs471
;; lisp
;;
;; evaluates a circuit design (CD)
;; (modified code from Shaun Cooper's lecture)
;;
;; must be given a CD
;;
;; NOT CD1

(define (evalcd CD)
	(cond ((null? CD) `())
		;; if the CD is null we have no more work to do
		;; base case
		((not (list? CD)) CD)
		;; can't break atoms up; return it
		((eq? (car CD) `NOT) (evalcd_not CD))
			;; call helper functions for evaluating each case

		))
		

;; pre: must be in (NOT CD) form
(define (evalcd_not CD)
	(cond ((eq? (evalcd (cadr CD)) 0) 1)
			;; not of 0 is 1
			((eq? (evalcd (cadr CD)) 1) 0)
			;; not is 1 is 0
		(else (cons (car CD) (list (evalcd (cadr CD)))))))
			;; deal with rest of CD (we took care of the NOT)
