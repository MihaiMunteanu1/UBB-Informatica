graph
[
  directed 0

  # Spania
  node [ id 1  label "FC Barcelona"        country "Spain" ]
  node [ id 2  label "Real Madrid"         country "Spain" ]
  node [ id 3  label "Atletico Madrid"     country "Spain" ]
  node [ id 4  label "Sevilla FC"          country "Spain" ]
  node [ id 5  label "Valencia CF"         country "Spain" ]

  # Anglia
  node [ id 6  label "Manchester United"   country "England" ]
  node [ id 7  label "Manchester City"     country "England" ]
  node [ id 8  label "Liverpool"           country "England" ]
  node [ id 9  label "Chelsea"             country "England" ]
  node [ id 10 label "Arsenal"             country "England" ]

  # Germania
  node [ id 11 label "Bayern Munich"       country "Germany" ]
  node [ id 12 label "Borussia Dortmund"   country "Germany" ]
  node [ id 13 label "RB Leipzig"          country "Germany" ]
  node [ id 14 label "Eintracht Frankfurt" country "Germany" ]
  node [ id 15 label "Bayer Leverkusen"    country "Germany" ]

  # Italia
  node [ id 16 label "Juventus"            country "Italy" ]
  node [ id 17 label "AC Milan"            country "Italy" ]
  node [ id 18 label "Inter Milan"         country "Italy" ]
  node [ id 19 label "AS Roma"             country "Italy" ]
  node [ id 20 label "Napoli"              country "Italy" ]

  # Spania - interne
  edge [ source 1 target 2 ]
  edge [ source 1 target 3 ]
  edge [ source 1 target 4 ]
  edge [ source 2 target 3 ]
  edge [ source 3 target 4 ]
  edge [ source 4 target 5 ]

  # Anglia - interne
  edge [ source 6 target 7 ]
  edge [ source 6 target 8 ]
  edge [ source 6 target 9 ]
  edge [ source 7 target 10 ]
  edge [ source 8 target 9 ]
  edge [ source 9 target 10 ]

  # Germania - interne
  edge [ source 11 target 12 ]
  edge [ source 11 target 13 ]
  edge [ source 12 target 14 ]
  edge [ source 13 target 15 ]
  edge [ source 14 target 15 ]

  # Italia - interne
  edge [ source 16 target 17 ]
  edge [ source 16 target 18 ]
  edge [ source 17 target 18 ]
  edge [ source 18 target 19 ]
  edge [ source 19 target 20 ]

  # European competition edges
  edge [ source 1 target 11 ]  # Barcelona - Bayern
  edge [ source 2 target 6 ]   # Real Madrid - Man Utd
  edge [ source 3 target 13 ]  # Atletico - Leipzig
  edge [ source 4 target 14 ]  # Sevilla - Frankfurt
  edge [ source 5 target 19 ]  # Valencia - Roma

  edge [ source 8 target 11 ]  # Liverpool - Bayern
  edge [ source 8 target 12 ]  # Liverpool - Dortmund
  edge [ source 9 target 16 ]  # Chelsea - Juventus
  edge [ source 10 target 18 ] # Arsenal - Inter
  edge [ source 7 target 20 ]  # Man City - Napoli

  edge [ source 13 target 18 ] # Leipzig - Inter
  edge [ source 12 target 17 ] # Dortmund - AC Milan
  edge [ source 14 target 19 ] # Frankfurt - Roma
  edge [ source 15 target 20 ] # Leverkusen - Napoli
]
