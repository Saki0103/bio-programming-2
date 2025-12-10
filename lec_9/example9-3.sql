SELECT
    v.var_id,
    g.gene_id
FROM
    variant AS v
INNER JOIN
    gene AS g
    ON v.chrom = g.chrom
   AND v.pos BETWEEN g.start_pos AND g.end_pos;