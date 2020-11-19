(define (countem L)
		(if (null? L)
			0
			(+ 1 (countem (cdr L)))))
