## Zip Code Finder

This was one of the first shell scripts I wrote and it it used to scrape the web to find certain zip codes. The program takes command line arguments so that the user can specify which zipcode(s) they want to find. I loved this assignment because it was my first experience with web scraping and I thought it was nice that when I finished the assignment I actually had a very useful tool. For more details about the program refer to the *report.txt* file. 

## Use

1. Clone the repository: `git clone https://github.com/slancas1/smaller_assignments.git`
2. Execute the zipcode.sh file: `./zipcode.sh`
	* During this step you can utilize any of the command line arguments listed below to make your search more specific

## Command Line Arguments

The different command line arguments are passed as flags when the executable is run.

1. **-h:** prints a usage message for the program
	* EXAMPLE: `./zipcode.sh -h`
2. **-c:** allows you to specify which city you want the zip code for
	* EXAMPLE: `./zipcode.sh -c Warsaw`
3. **-f:** allows you to specify which format the zip codes should be displayed in
	* EXAMPLE: `./zipcode.sh -f csv`
4. **-s:** allows you to specify which state you want the zip code for
	* EXAMPLE: `./zipcode.sh -s Indiana`


