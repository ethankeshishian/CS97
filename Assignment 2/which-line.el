(defun which-line ()
  "Print the current buffer line number and narrowed line number of point."
  (interactive)
  (let ((start (point-min))
	(n (line-number-at-pos))
	(numLines (how-many "\n" (point-min) (point-max))))
    (if (= start 1)
	(message "Line %d of %d" n numLines)
      (save-excursion
	(save-restriction
	  (widen)
	  (message "line %d (narrowed line %d)"
		   (+ n (line-number-at-pos start) -1) n))))))
