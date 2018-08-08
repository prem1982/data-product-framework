#!/usr/bin/env bash

FULL_LINTER_RESULT=$( ./build/cpplint.py --linelength 120 --extensions=cpp --headers=hpp --filter=-build/header_guard,-legal/copyright --counting=detailed  $( find . -name *.hpp -or -name *.cpp ) );
LAST_LINE=$( echo "$FULL_LINTER_RESULT" | tail -1 )

if [[ $LAST_LINE == "Total errors found: 0" ]]; then
  echo $LAST_LINE
else
  echo "$FULL_LINTER_RESULT"
fi
