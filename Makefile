all	:	client server

clean	:
	$(MAKE) -C client clean
	$(MAKE) -C server clean

fclean	:
	$(MAKE) -C client fclean
	$(MAKE) -C server fclean

re	:	fclean all

client	:
	$(MAKE) -C client all

server	:
	$(MAKE) -C server all

.PHONY	:	clean fclean all re client server
