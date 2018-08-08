#!/usr/bin/env bash
 
# Capture output path from args
OUTPUT_PATH=$1
shift

# Run pylint on all python source files, direct reports to pylint.log
EXIT_STATUS=0
while (($#)); do
    echo "Running pylint on $1:" >> ${OUTPUT_PATH}/pylint.log
    echo "=================" >> ${OUTPUT_PATH}/pylint.log
    pylint --rcfile=./.pylintrc --persistent=n --score=n ${1} &>> ${OUTPUT_PATH}/pylint.log
    if [ $? -ne 0 ]; then
        EXIT_STATUS=1
    fi
    echo -e "=================\n\n\n" >> ${OUTPUT_PATH}/pylint.log

    shift
done

# Display useful message to users
RED='\033[0;31m'
GREEN='\033[0;32m'
NO_COLOR='\033[0m'
if [ $EXIT_STATUS -eq 0 ]; then
    echo -e "${GREEN}"
    echo "pylint detected no issues."
    echo -e "${NO_COLOR}"
else
    echo -e "${RED}"
    echo "pylint detected issues, see log at:"
    echo "${OUTPUT_PATH}/pylint.log"
    echo -e "${NO_COLOR}"
    cat ${OUTPUT_PATH}/pylint.log
fi

exit $EXIT_STATUS

