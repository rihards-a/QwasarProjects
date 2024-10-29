# Welcome to My Select Query
***

## Task
The task is to create a class MySelectQuery that parses CSV data and allows users to query specific rows based on unique column values.

## Description
The MySelectQuery class takes a CSV-formatted string as input, extracts headers, and stores the data as an array of hashes for easy access. 
The class offers a where method that allows users to find rows matching specific criteria in a designated column, returning a formatted string of the row's values.

## Installation
The project needs no installation, simply ensure that you have Ruby installed and have the script.

## Usage
To use the MySelectQuery class, you can create a new instance by passing in your CSV data as a string and then call the where method to find specific entries:
    query = MySelectQuery.new(csv_data)
    result = query.where("name", "Alaa Abdelnaby")
using puts result will output a formatting string of the csv row matching the query
