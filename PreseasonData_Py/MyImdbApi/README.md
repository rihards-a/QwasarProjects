# Welcome to My Imdb Api
***

## Task
The task is to build a backend API that mimics some of the functionality of IMDB by providing a movie search feature based on genre. 
This API reads from a CSV file containing movie data and allows users to filter and retrieve movies based on their genre. 
The challenge is satisfying Gandalf - finding the correct formatting option

## Description
This project solves the problem of querying movie information by genre from a provided CSV file. 
The application is built using Flask, a Python micro web framework, which handles HTTP requests and responses. 
The CSV file is parsed, and the API filters out movies of specific genres, returning the results in JSON format. 
Each genre is served through individual routes like /action, /comedy, etc., and the base route allows redirection based on query parameters.

## Installation
Clone this repository to your local machine.
Make sure you have Python and Flask installed.
Ensure that the CSV file imdb-movie-data.csv is in the same directory as the script.

## Usage
Start the server:
python app.py
Once the server is running, you can query it using cURL or directly from a browser.
