WITH kevin_bacon_movies AS (
  SELECT movie_id
  FROM stars
  JOIN people ON people.id = stars.person_id
  WHERE people.name = 'Kevin Bacon' AND people.birth = 1958
)

SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN kevin_bacon_movies ON kevin_bacon_movies.movie_id = stars.movie_id
WHERE people.name != 'Kevin Bacon';
