;; This is actually less complicated than the 218 challenge
;; because I didn't bother with a menu system or nice input.
;; I just stuck with the original challenge of writing the functions.

;; Turn this isn't a hash-table to be able to categorize things
(defparameter *todo-list* (make-hash-table :test #'equalp))
(defparameter *categories* ())

;; Updated to handle categories
(defun viewList-helper (category)
  (format t "~&     ~A:~%" category)
  (do ((x (gethash category *todo-list*) (cdr x))
       (i 0 (1+ i)))
      ((eql 0 (length x)) nil)
    (format t"- ~A~%" (car x)))
  (format t "~%"))

;; Now will call the correct categories, can handle multiple
;; categories
(defun viewList (&rest category)
  (if category
      (mapcar #'viewList-helper category)
      (mapcar #'viewList-helper *categories*)))

;; Works like project spec
(defun addItem (item &rest category)
  (if (not category)
      (push "Uncategorized" category))
  (mapcar (lambda (cat)
	    (if (not (position cat *categories* :test #'equalp))
		(setf *categories* (push cat *categories*))))
	  category)
  (mapcar (lambda (cat)
	    (setf (gethash cat *todo-list*)
		  (append (gethash cat *todo-list*) (list item))))
	  category))

;;; Should not be called directly
(defun deleteItem-helper (item-number category)
  (let ((x (gethash category *todo-list*)))
    (if (<= item-number (length x))
	(setf (gethash category *todo-list*)
	      (append (subseq x 0 (1- item-number))
		      (subseq x item-number))))))

;; This works like the original project wanted
;; The item is not case sensitive
(defun deleteItem (item &rest category)
  (mapcar (lambda (cat)
	    (let ((x (position item (gethash cat *todo-list*)
			       :test #'string-equal)))
	      (if x
		  (deleteItem-helper (1+ x) cat))))
	  (if category category *categories*)))

(defun updateItem-helper (item-number new-item category)
  (let ((x (gethash category *todo-list*)))
    (if (<= item-number (length x))
	(setf (gethash category *todo-list*)
	      (append (subseq x 0 (1- item-number))
		      (list new-item)
		      (subseq x item-number))))))

(defun updateItem (old-item new-item &rest category)
  (mapcar (lambda (cat)
	    (let ((x (position old-item (gethash cat *todo-list*)
			       :test #'string-equal)))
	      (if x (updateItem-helper (1+ x) new-item cat))))
	  (if category category *categories*)))
