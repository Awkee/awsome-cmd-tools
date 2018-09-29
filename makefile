
CC 		= gcc
CFLAGS 	= 
LDFLAGS = 

DEST_DIR=bin
INSTALL_PATH=./bin


TARGET_FILE = li lst lsdir rename 
TARGET_DATE = ndays
TARGETS		= ${TARGET_FILE} ${TARGET_DATE}

all: ${TARGET_FILE} ${TARGET_DATE}

${TARGET_FILE}:
	cd file && ${CC} -o $@ $@.c ${LDFLAGS} && cd ../ && ( [ -d ${DEST_DIR} ] && mv file/$@  ${DEST_DIR} )

${TARGET_DATE}:
	cd date && ${CC} -o $@ $@.c ${LDFLAGS} && cd ../ && ( [ -d ${DEST_DIR} ] && mv date/$@  ${DEST_DIR} )

clean:
	rm -f *.o core

purge:
	cd ${INSTALL_DIR} && rm -f ${TARGETS} 

install:
	( [ -z "${INSTALL_PATH}" ] && echo  'you should run make install INSTALL_PATH=./bin ' ) || ( cd ${DEST_DIR} && mv ${TARGETS} "${INSTALL_PATH}" )

