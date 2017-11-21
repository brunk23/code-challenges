(define (abs x)
  (if (< x 0) (- x) x))

(define (good-enough? original guess)
  (< (abs (- original (* guess guess guess))) 0.00001))

(define (improve-cube-guess original guess)
  (/ (+ (/ original (* guess guess)) (* 2 guess)) 3))

(define (cube-root-iter original guess)
  (if (good-enough? original guess)
      guess
      (cube-root-iter original (improve-cube-guess original guess))))

(define (cuberoot x)
  (cube-root-iter x 1.0))
