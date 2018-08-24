
CC 		= gcc
CFLAGS 	= 
LDFLAGS = 

INSTALL_DIR=bin

TARGET_FILE = li lst lsdir rename 
TARGET_DATE = ndays
TARGETS		= ${TARGET_FILE} ${TARGET_DATE}

all: ${TARGET_FILE} ${TARGET_DATE}

${TARGET_FILE}:
	cd file && ${CC} -o $@ $@.c ${LDFLAGS} && cd ../ && ( [ -d ${INSTALL_DIR} ] && mv file/$@  ${INSTALL_DIR} )

${TARGET_DATE}:
	cd date && ${CC} -o $@ $@.c ${LDFLAGS} && cd ../ && ( [ -d ${INSTALL_DIR} ] && mv date/$@  ${INSTALL_DIR} )

clean:
	rm -f *.o core

purge:
	cd ${INSTALL_DIR} && rm -f ${TARGETS} 

install:
	 @ ( [ -z "${INSTALL_PATH}" ] && echo  'you should run make install INSTALL_PATH=./bin ' ) || mv ${TARGETS} "${INSTALL_PATH}" 

