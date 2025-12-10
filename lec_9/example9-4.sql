SELECT
    e.tpm,
    s.tissue,
    s.disease
FROM
    expression AS e
INNER JOIN
    sample AS s
      ON e.sample_id = s.sample_id
WHERE
    e.gene_id = 'G1';
