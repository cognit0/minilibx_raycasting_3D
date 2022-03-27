NAME = 3d
LIB = -lmlx -lm
SOURCE = main.c 3d_util.c #3d_rays.c
OBJECT = main.o	3d_util.o #3d_rays.o
FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)
	
$(NAME): $(OBJECT)
	@gcc -o $(NAME) $(OBJECT) $(LIB) $(FRAMEWORKS)
	@echo "============================="
	@echo "============================="
	@echo "=         EXE READY         ="
	@echo "============================="
	@echo "============================="
	@rm -rf *.o

$(OBJECT) : $(SOURCE)
	@gcc -c $(SOURCE)

clean: 
	@rm -rf $(NAME)

re:
	@make clean
	@make -C ./
