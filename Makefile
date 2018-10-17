CFLAGS=-Wall -g
# -Wall: all warnings possible

all:	test primitive_print_format c_array c_array2 echo_arguments disect_arguments pointers_and_loops struct mock_email_db pointer_to_function c_array3 dbg_macros_test io my_scanf

# the above builds the target executable just like below command
# --------------------------------------------------------------
# all:
	# make ex1

clean:
	rm -f test primitive_print_format c_array c_array2 echo_arguments disect_arguments pointers_and_loops struct mock_email_db pointer_to_function c_array3 dbg_macros_test io my_scanf
	rm -rf `find . -name "*.dSYM" -print`
