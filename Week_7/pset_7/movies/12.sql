SELECT movies.title AS "title"
FROM movies
JOIN stars AS sc ON sc.movie_id = movies.id
JOIN people AS bradley_cooper ON bradley_cooper.id = sc.person_id
JOIN stars AS sl ON sl.movie_id = movies.id
JOIN people AS jennifer_lawrence ON jennifer_lawrence.id = sl.person_id
WHERE bradley_cooper.name = 'Bradley Cooper'
  AND jennifer_lawrence.name = 'Jennifer Lawrence';
