### EXPORT TO CSV

From raspi console ( ssh )
      influx
      SELECT * from sensor where (\"user\" = 'USER NAME')

From console  

influx -database 'datagas' -execute "SELECT * from sensor where (\"user\" = 'en scred')" -format csv > en_scred.csv
