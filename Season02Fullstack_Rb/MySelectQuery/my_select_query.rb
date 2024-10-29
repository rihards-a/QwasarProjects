class MySelectQuery
    # def initialize() is intended, no? Not constructor()
    def initialize(csv_content)
        # @ for class scope use
        @data = []
        rows = csv_content.split("\n")
        headers = rows[0].split(",")
        # skips the first row because it's the headers
        rows[1..].each do |row|
            # zip stitches the 2 together into a single key value pair for each value
            @data << Hash[headers.zip(row.split(","))]
        end
    end
    def where(column_name, criteria)
        # .find/.select accesses the row that matches the criteria via dictionary/hash 
        # the map ensures that we don't return the whole hash but only the key values in a joined format
        # return [(@data.find {|row| row[column_name]==criteria}).values.join(",")] - if we know there is only 1 matching value
        return (@data.select{|row| row[column_name]==criteria}) .map{|row| row.values.join(",")} # - for potentially multiple results
    end
end
