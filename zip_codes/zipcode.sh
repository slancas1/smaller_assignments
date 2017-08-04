#!/bin/sh

# if statement that displays the usage message if the -h flag is passed
if [ "$1" == "-h" ]; then
    cat <<EOF
Usage: zipcode.sh

	-c      CITY    Which city to search
    -f      FORMAT  Which format (text, csv)
    -s      STATE   Which state to search (Indiana)
      
If not CITY is specified, then all the zip codes for the STATE are displayed.
EOF
	exit 1
fi

# declares and initializes variables used to deal with the different flags
CITYSET="false"
TEXT="false"
CSV="false"
STATE="Indiana"
STATESET="false"

# while loop that executes as long as the number of arguments is greater 
	# than 0 -- goes through each argument to see if it is a -c, -s, or -f flag
while [ "$#" -gt 0 ] 
do
	# if there is a -c flag the CITY variable gets set to the argument
		# after the flag and the CITYSET variable gets set to true
    if [ "$1" == "-c" ]; then
    	shift
    	CITY="$1"
    	CITYSET="true"
    fi
    # if there is a -f flag the argument after the flag is checked
    if [ "$1" == "-f" ]; then
    	shift
    	# if the argument after the flag is "text" the TEXT variable gets set to true
    	if [ "$1" == "text" ]; then
    		TEXT="true"
    	# if the argument after the flag is "csv" the CSV variable gets set to true
    	elif [ "$1" == "csv" ]; then
    		CSV="true"
    	fi	
    fi
    # if there is a -s flag the STATE variable gets set to the argument
    	# after the flag and the STATESET variable gets set to true 
    if [ "$1" == "-s" ]; then
    	shift
    	STATE="$1"
    	STATE=$(echo "$STATE" | sed -E 's/ /%20/g') # if the name has a space in it the space gets set to the URL character for space
    	STATESET="true"
    fi
    shift
done

# if statement that executes if the STATESET variable is false
if [ "$STATESET" == "false" ]; then
	# if the TEXT variable is true all the zip codes of Indiana get displayed one line at a time
	if [ "$TEXT" == "true" ]; then
		curl -s http://www.zipcodestogo.com/Indiana/ | grep -Eo '[0-9]{5}/' | cut -c 1-5
	# if the CSV variable is true all the zip codes of Indiana get displayed as CSV	
	elif [ "$CSV" == "true" ]; then
		curl -s http://www.zipcodestogo.com/Indiana/ | grep -Eo '[0-9]{5}/' | cut -c 1-5 | tr '\n' ', ' | rev | cut -c 2- | rev
	# or else the zip codes of Indiana get displayed one line at a time
	else 
		curl -s http://www.zipcodestogo.com/Indiana/ | grep -Eo '[0-9]{5}/' | cut -c 1-5
	fi
# elif statement that executes if the STATESET variable is true	
elif [ "$STATESET" == "true" ]; then
	# if statement that executes if the TEXT variable is true
	if [ "$TEXT" == "true" ]; then
		# if the CITYSET variable is false all of the zip codes of the indicated state get displayed one line at a time
		if [ "$CITYSET" == "false" ]; then
			curl -s http://www.zipcodestogo.com/"$STATE"/ | grep -Eo '[0-9]{5}/' | cut -c 1-5
		# if the CITYSET variable is true the zipcode(s) of the indicated city get displayed one line at a time
		elif [ "$CITYSET" == "true" ]; then
			curl -s http://www.zipcodestogo.com/"$STATE"/ | grep -E "/$CITY/" | grep -Eo '[0-9]{5}' | sort | uniq
		fi
	# elif statement that executes if the CSV variable is true
	elif [ "$CSV" == "true" ]; then
		# if the CITYSET variable is false all of the zip codes of the indicated state get displayed as CSV
		if [ "$CITYSET" == "false" ]; then
	    	curl -s http://www.zipcodestogo.com/"$STATE"/ | grep -Eo '[0-9]{5}/' | cut -c 1-5 | tr '\n' ', ' | rev | cut -c 2- | rev
		# if the CITYSET variable is true the zipcode(s) of the indicated city get displayed as CSV
		elif [ "$CITYSET" == "true" ]; then
	    	curl -s http://www.zipcodestogo.com/"$STATE"/ | grep -E "/$CITY/" | grep -Eo '[0-9]{5}' | sort | uniq | tr '\n' ', ' | rev | cut -c 2- | rev
		fi
	# if neither of the format settings was indicated this if statement is entered
	else 
		# if the CITYSET variable is false all of the zip codes of the indicated state get displayed one line at a time
		if [ "$CITYSET" == "false" ]; then
			curl -s http://www.zipcodestogo.com/"$STATE"/ | grep -Eo '[0-9]{5}/' | cut -c 1-5
		# if the CITYSET variable is true the zipcode(s) of the indicated city get displayed one line at a time
		elif [ "$CITYSET" == "true" ]; then
			curl -s http://www.zipcodestogo.com/"$STATE"/ | grep -E "/$CITY/" | grep -Eo '[0-9]{5}' | sort | uniq 
		# or else the zip codes of the indicated state get displayed one line at a time
		else
			curl -s http://www.zipcodestogo.com/"$STATE"/ | grep -Eo '[0-9]{5}/' | cut -c 1-5
		fi	
	fi	
fi

