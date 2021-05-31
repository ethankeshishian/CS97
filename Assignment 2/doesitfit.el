(defun doesitfit ()
  "Checks if 2^3^4 fits in a 64-bit integer."
  (let ((maxSize (- (expt 2 64) 1)))
    (if (< (expt 2 (expt 3 4)) maxSize)
	   (message "t")
	   (message "nil"))))

