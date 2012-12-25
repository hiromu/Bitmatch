(defun scoring (lst)
  (let ((lst-sum (reduce #'+ lst)))
    (cond
      ((eq lst-sum 0) 0)
      ((eq lst-sum 1) 1)
      ((or (equal lst '(1 0 0 1))
	   (equal lst '(1 0 1 0))
	   (equal lst '(0 1 0 1))) 2)
      ((or (equal lst '(0 0 1 1))
	   (equal lst '(0 1 1 0))
	   (equal lst '(1 1 0 0))) 3)
      ((or (equal lst '(1 1 0 1))
	   (equal lst '(1 0 1 1))) 4)
      ((or (equal lst '(0 1 1 1))
	   (equal lst '(1 1 1 0))) 5))))

(defun ubit-shift (bit-list n)
;  (when (> (abs n) 3) (error "Error: N >= 4"))
  (cond ((plusp n) (append (nthcdr n bit-list)
			   (make-list n :initial-element 0)))
	(t (append (make-list (abs n) :initial-element 0)
		   (butlast bit-list (abs n))))))

(defun my-xor (n m)
  (if (eq n m) 0 1))

(defun ubit-xor (list1 list2)
  (mapcar #'my-xor list1 list2))

;(reverse enemy)

(defun iota (n m)
  (if (< n m)
      (loop for i from n upto m collect i)
      (loop for i from n downto m collect i)))

(defun shifted-list (lst)
  (loop for i from -3 to 3 collect (ubit-shift lst i)))

(defun alt-e (right left)
  (if (< (scoring right) (scoring left)) left
      right))
(defun alt-m (right left)
  (if (> (scoring right) (scoring left)) left
      right))

(defvar right-e)
(defvar right-m)
(defvar left-e)
(defvar left-m)

(defun rl-e (n)
  (if (equal n right-e) 1
      0))
(defun rl-m (n)
  (if (equal n right-m) 1
      0))

(defun hoge (me ene)
  (let ((shift -3))
    (loop for i in (shifted-list me)
       collect (list (scoring (ubit-xor i ene))
		     (rl-m me) (rl-e ene)
		     (incf shift)))))

(defun ubit-read ()
  (read-line)
  (setf left-m (read-from-string (format nil "(~a)" (read-line))))
  (setf right-m (read-from-string (format nil "(~a)" (read-line))))
  (setf left-e (read-from-string (format nil "(~a)" (read-line))))
  (setf right-e (read-from-string (format nil "(~a)" (read-line)))))

(defun foo ()
  (format t "~{~a~^ ~}~&"
	  (cdar
	   (sort (hoge (alt-m right-m left-m) (alt-e right-e left-e))
		 (lambda (n m) (> (car n) (car m)))))))
(defun bar (n)
  (eq (mapcar #'+ n) 4))

(defun main ()
  (ubit-read)
  (unless (or (and (bar right-m) (bar left-m)) (and (bar right-e) (bar left-e)))
    (foo)
    (main)))

(main)
