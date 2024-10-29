from os import path # for accessing csv
import csv # for oppening csv
from json import dumps
from flask import Flask, request, redirect
app = Flask(__name__)

'''
HTTP status codes:
200 OK - response matches request
204 No Content - processed request but no content
400 Bad Request - server cannot or will not process due to a client error
401 Unauthorized - authentication required but hasn't been provided
500 Internal Server Error - unexpected condition and no specific message is suitable
- handled by flask
'''

# finds all the movies that include the specified genre in their csv values
def fn_for_parsing_csv(genre):
    final_movies = []
    # gets the full directory path of the script/program on any machine - works only if csv is in the same directory
    with open(path.join(path.dirname(path.abspath(__file__)), 'imdb-movie-data.csv'), 'r') as csv_file:
        reader = csv.reader(csv_file)  # Use csv.reader to read rows as lists
        headers = next(reader)  # Get the header row (column names)
        for row in reader:
            genres = map(lambda x: x.lower(), row[headers.index("Genre")].split(','))
            if genre in genres:
                # movie_dict = {headers[i]: row[i] for i in range(len(headers))} <-- shorter version for generating dictionaries
                movie_dict = {}
                for i in range(len(headers)):
                    movie_dict[headers[i]] = row[i]
                final_movies.append(movie_dict)
    return dumps(final_movies)

# redirector for GET requests
@app.route('/', methods=['GET'])
def handlinggetgenre():
    if request.method == 'GET':
        genre = request.args.get("genre")
        list_of_genres = ["Action", "Adventure", "Sci-Fi", "Mystery", "Horror", "Thriller", "Animation", "Comedy", "Family", "Fantasy", "Drama", "Music", "Biography", "Romance", "History", "Crime", "Western", "War", "Musical", "Sport"]
        if genre: 
            for matching_genre in list_of_genres:
                if genre == matching_genre.lower():
                    return redirect("/" + genre)
    # if no GET request has been made - display the whole csv file
    final_movies = []
    with open(path.join(path.dirname(path.abspath(__file__)), 'imdb-movie-data.csv'), 'r') as csv_file:
        reader = csv.reader(csv_file)  # Use csv.reader to read rows as lists
        headers = next(reader)  # Get the header row (column names)
        for row in reader:
            movie_dict = {}
            for i in range(len(headers)):
                movie_dict[headers[i]] = row[i]
            final_movies.append(movie_dict)
    return dumps(final_movies)

@app.route('/<genre>')
def show_movies_with_genre(genre):
    if genre in map(lambda x: x.lower(), ["Action", "Adventure", "Sci-Fi", "Mystery", "Horror", "Thriller", "Animation", "Comedy", "Family", "Fantasy", "Drama", "Music", "Biography", "Romance", "History", "Crime", "Western", "War", "Musical", "Sport"]):
        return fn_for_parsing_csv(genre)

# not sure if Gandalf will like main
if __name__ == '__main__':
   app.run(host='0.0.0.0', port=8080)

'''
GET is used to request data from a specified resource.
Note that the query string (name/value pairs) is sent in the URL of a GET request:
/test/demo_form.php?name1=value1&name2=value2
POST is used to send data to a server to create/update a resource.
The data sent to the server with POST is stored in the request body of the HTTP request:
POST /test/demo_form.php HTTP/1.1
Host: w3schools.com
name1=value1&name2=value2
'''
