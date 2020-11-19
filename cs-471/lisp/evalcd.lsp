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
		;; evaluate NOT
		((eq? (car CD) `AND) (evalcd_and CD))
		;; evaluate AND
		((eq? (car CD) `OR) (evalcd_or CD))
		;; evaluate OR

		))
		

;; pre: must be in (NOT CD) form, (CAR CD) -> NOT
;; post: apply simple tautologies to CD
(define (evalcd_not CD)
	(cond ((eq? (evalcd (cadr CD)) 0) 1)
			;; not of 0 is 1
			((eq? (evalcd (cadr CD)) 1) 0)
			;; not is 1 is 0
		(else (cons `NOT (list (evalcd (cadr CD)))))))
			;; deal with rest of CD (we took care of the NOT)


;; pre: must be in (AND CD1 CD2) form
;; post: apply simple tautologies to CD1 and CD2, and may reduce AND
(define (evalcd_and CD)
	(cond ((eq? (evalcd (cadr CD)) 0) 0)
			;; if first arg is 0 then return 0
			((eq? (evalcd (caddr CD)) 0) 0)
			;; if second arg is 0 then return 0

			((eq? (evalcd (cadr CD)) 1) (evalcd (caddr CD)))
			;; if first arg is 1, return whatever the second arg is
			((eq? (evalcd (caddr CD)) 1) (evalcd (cadr CD)))
			;; if second arg is 1, return whatever the first arg is

		(else (cons `AND 
				(list (evalcd (cadr CD)) (evalcd (caddr CD)))
				;; evaluate the rest of the list after the part we
				;; already examined
		))))


;; pre: must be in (OR CD1 CD2) form
;; post: apply simple tautologies to CD1 and CD2, and may reduce OR
(define (evalcd_or CD)
	(cond ((eq? (evalcd (cadr CD)) 1) 1)
			;; if first arg is 1 then return 1
			((eq? (evalcd (caddr CD)) 1) 1)
			;; if second arg is 1 then return 1
			((eq? (evalcd (cadr CD)) (evalcd (caddr CD)))
					(evalcd (cadr CD)))
			;; if both args are equal, return their value (handles 0 0)

			((eq? (evalcd (cadr CD)) 0) (evalcd (caddr CD)))
			;; if first arg is 0, return whatever the second arg is
			((eq? (evalcd (caddr CD)) 0) (evalcd (cadr CD)))
			;; if second arg is 0, return whatever the first arg is

		(else (cons `OR
				(list (evalcd (cadr CD)) (evalcd (caddr CD)))
				;; evaluate the rest of the list after the part we
				;; already examined
		))))




