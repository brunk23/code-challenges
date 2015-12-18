;; http://www.reddit.com/r/dailyprogrammer/comments/39ws1x/20150615_challenge_218_easy_todo_list_part_1/

;; It should have the following basic functionality
;;    Add an item to the to-do list
;;    Delete a selected item from the to-do list
;;    And obviously, print out the list so I can see what to do!

;(defparameter *todo-list* nil)

(defun print-list (lst &key (count 1) (numbers t))
  (fresh-line)
  (if lst
      (progn
	(if numbers
	    (format t "~A. " count))
	(format t"~A~%" (car lst))
	(print-list (cdr lst) :count (1+ count) :numbers numbers))
      (format t "~%")))

(defun add-item (item lst)
  (append lst (list item)))

(defun remove-item (item-number lst)
  (if (<= item-number (length lst))
      (append (subseq lst 0 (1- item-number))
	      (subseq lst item-number))
      lst))

(defun print-menu ()
  (format t "1. Add an item to the list~%")
  (format t "2. Remove an item to the list~%")
  (format t "3. Print the list~%")
  (format t "4. Quit~%~%What do you want to do: "))

(defun get-new-item ()
  (format t "New item: ")
  (read-line))

(defun get-item-number (lst)
  (labels ((menu ()
	     (print-list lst)
	     (format t "~A. Return to main menu~%~%Which one: "
		     (1+ (length lst)))))
    (do ((x 0 (read)))
	((and (> x 0) (<= x (1+ (length lst)))) x)
      (menu))))

;; This works like the original project wanted
(defun addItem (item)
  (setf *todo-list* (add-item item *todo-list*)))

;; This works like the original project wanted
;; The item is not case sensitive
(defun deleteItem (item)
  (let ((x (position item *todo-list* :test #'string-equal)))
    (if x
	(setf *todo-list* (remove-item (1+ x) *todo-list*))
	(format t "Error: \"~A\" does not appear to exist.~%" item))))

;; This works like the original project wanted
(defun viewList ()
  (print-list *todo-list* :numbers nil))

(defun main ()
  (do ((inp nil (read)))
      ((equal inp 4) nil)
    (case inp
      (1 (setf *todo-list* (add-item (get-new-item) *todo-list*)))
      (2 (setf *todo-list*
	       (remove-item (get-item-number *todo-list*) *todo-list*)))
      (3 (print-list *todo-list*))
      (t nil))
    (print-menu)))
