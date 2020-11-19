(define (countemall L)
	(cond	((null? L) 0)
			((not	(list? L) 1)
			(else	(+	(countemall	(car L))
						(countemall	(cdr L)))))))

