from scipy import sparse
help(sparse)			# check the functions of module sparse

# coo_matrix : use row, column, and value to create a matrix, however it cannot insert and delete elements
row = [2, 2, 3]
col = [3, 4, 2]
data = [8, 9, 10]
c = sparse.coo_matrix((data, (row,col)), shape=(5,5))
print(c.toarray())

# dok_matrix : use dictionary to store the element which isn't zero, add the element one by one
d = sparse.dok_matrix((5,5), dtype=np.int16)
for i in range(5):
    for j in range(5):
        d[i, j] = i + j       
print(d.toarray())

# lil_matrix : store the element one by one
l = sparse.lil_matrix((5,5), dtype=np.int16)
l[2, 4] = 3
l[3, 3] = 5
l[1, 2] = 7
print(l.toarray())
