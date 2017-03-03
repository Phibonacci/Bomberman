# All the default variables used in this Makefile are commented with their
# definition and their default value.
# Read the Make manual at gnu.org for more informations.
# https://www.gnu.org/software/make/manual/

# VARIABLES

NAME		=	bomberman
#  CC
#  Program for compiling C programs; default ‘cc’.
CXX		=	g++

LIBPATH		= ../
INCLUDES	=	-I ./src/include -I ./ -I Entity/ -I Modules/ -I Board/

DEBUG		=	0
BUILD		=	build

SRC		= \
		main.cpp \
		GamePlayer.cpp \
		GameIA.cpp \
		GameParty.cpp \
		GameEngine.cpp \
		DrawComponent.cpp \
		Direction.cpp \
		DrawModel.cpp \
		Player.cpp \
		SaveLoad.cpp \
		EntityFactory.cpp \
		TeleportCenter.cpp
#  VPATH
#  https://www.gnu.org/software/make/manual/make.html#Directory-Search
VPATH		=	src
INCLUDES	+=	-I ./ -I ../utils

SRC		+= \
		Thread.cpp \
		Mutex.cpp \
		Lock.cpp

VPATH		+=	:./CThread
INCLUDES	+=	-I ./CThread/

SRC		+= \
		GameIntro.cpp

VPATH		+=	:./Intro/
INCLUDES	+=	-I ./Intro/

SRC		+= \
		ModelDraw.cpp \
		ModelDrawLarger.cpp \
		Move.cpp \
		MoveWall.cpp \
		Hitbox.cpp \
		BombMake.cpp \
		EditMake.cpp \
		Entity.cpp \
		OnTouch.cpp \
		Destruction.cpp \
		LifeTimer.cpp \
		Bonus.cpp \
		HasPlayer.cpp \
		HasBonus.cpp \
		CanKick.cpp \
		OnDestroy.cpp \
		Needle.cpp \
		Position.cpp \
		BombType.cpp \
		ComponentFactory.cpp \
		Teleport.cpp \
		RotateDraw.cpp

VPATH		+=	:./Component
INCLUDES	+=	-I ./Component

SRC		+= \
		Board.cpp \
		Part.cpp
VPATH		+=	:./Board
INCLUDES	+=	-I ./Board

SRC		+= \
		Peripheral.cpp \
		MasterController.cpp \
		PlayerDir.cpp \
		Joystick.cpp \
		AI.cpp
VPATH		+=	:./Controller
INCLUDES	+=	-I ./Controller

SRC		+=	Rand.cpp \
			Content.cpp \
			ContentPlayer.cpp \
			Case.cpp \
			MapLoader.cpp \
			Checks.cpp

VPATH		+=	:./MapGen
INCLUDES	+=	-I ./MapGen

SRC		+=	AScreen.cpp \
			ACamera.cpp \
			ASubScreen.cpp

VPATH		+=	:./Screen
INCLUDES	+=	-I ./Screen

# SRC		+=	Lua.cpp
# VPATH		+=	:./Lua
# INCLUDES	+=	-I ./Lua

SRC		+=	ConfigLoader.cpp \
			Scoring.cpp
VPATH		+=	:./ConfigLoader
INCLUDES	+=	-I ./ConfigLoader


SRC		+=	Menus.cpp \
			Info.cpp
VPATH		+=	:./menu
INCLUDES	+=	-I ./menu

SRC		+=	Sound.cpp
VPATH		+=	:./Sound
INCLUDES	+=	-I ./Sound

SRC		+=	Pause.cpp
VPATH		+=	:./Pause
INCLUDES	+=	-I ./Pause

SRC		+=	MapEditor.cpp
VPATH		+=	:./Editor
INCLUDES	+=	-I ./Editor

SRC		+=	DirReader.cpp
VPATH		+=	:./DirReader
INCLUDES	+=	-I ./DirReader

#  CXXFLAGS
#  Extra flags to give to the C++ compiler.
INCLUDES 	+= -I$(LIBPATH)/LibBomberman_linux_x64/includes/ -I../gameplay/entity/
CXXFLAGS	+=	-Wall -Wextra
#  IFEQ
#  https://www.gnu.org/software/make/manual/make.html#index-ifeq_002c-expansion-110
#  FILTER
#  https://www.gnu.org/software/make/manual/make.html#index-filter-587
ifeq ($(DEBUG), $(filter $(DEBUG), 1 yes YES))
 CXXFLAGS	+=	-ggdb3 -D DEBUG
endif
CXXFLAGS	+=	$(INCLUDES)
#  CPPFLAGS
#  Extra flags to give to the C preprocessor and programs that use it (the C and
#  Fortran compilers).
CPPFLAGS	=
#  LDFLAGS
#  Extra flags to give to compilers when they are supposed to invoke the linker,
#  ‘ld’, such as -L.
#  Libraries (-lfoo) should be added to the LDLIBS variable instead.
#  e.g.: -L /usr/lib
LDFLAGS		= #-L./
#  LDLIBS
#  Library flags or names given to compilers when they are supposed to invoke
#  the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative
#  to LDLIBS. Non-library linker flags, such as -L, should go in the LDFLAGS
#  variable.
#  e.g.: -lphtread
LDLIBS		=

LDFLAGS		=  -L$(LIBPATH)LibBomberman_linux_x64/libs/ -lm -lgdl_gl -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -lGL -ldl -llua5.2 -lsfml-audio #`pkg-config sfml-audio --libs` `pkg-config sfml-system --libs`

OBJ		=	$(patsubst %.cpp,$(BUILD)/%.o,$(SRC))

MKDIR		=	mkdir -p
RMDIR		=	rm -rf
#  RM
#  Command to remove a file; default ‘rm -f’.
RM		=	rm -f

# RULES

all		:	$(BUILD) $(NAME)

$(BUILD)	:
		$(MKDIR) $(BUILD)

#  See:
#  Automatic Variables:
#  https://www.gnu.org/software/make/manual/make.html#Automatic-Variables
#  Implicit Rules
#  https://www.gnu.org/software/make/manual/make.html#Using-Implicit
.SUFFIXES	:	.cpp .o
$(BUILD)/%.o	:	%.cpp
		$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(NAME)		:	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean		:
		$(RM) $(OBJ)
ifeq ($(wildcard $(BUILD)), $(BUILD))
		rm -rf $(BUILD)
endif

fclean		:	clean
		$(RM) $(NAME)

drpropper	:	fclean

re		:	fclean all

.PHONY		:	all clean fclean mrpropper re
