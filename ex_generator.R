


A_F_1 <- matrix(LETTERS, ncol = 3, nrow = 2)

A_F_1 <- data.frame(A_F_1, stringsAsFactors = FALSE)

head(A_F_1)

write.csv(A_F_1, 'A_F_1.csv', row.names=FALSE)




B_1_A_199 <- matrix('A', ncol = 200, nrow = 1)

B_1_A_199[1,1] <- 'B'

B_1_A_199 <- data.frame(B_1_A_199)

head(B_1_A_199)

write.csv(B_1_A_199, 'B_1_A_199.csv', row.names=FALSE)


random_1000 <- matrix(LETTERS, ncol = 200, nrow = 100000)

random_1000 <- data.frame(random_1000, stringsAsFactors = FALSE)

write.csv(random_1000, 'random_1000.csv', row.names=FALSE)



random_1000_2 <- matrix(LETTERS, ncol = 200, nrow = 3200000)

random_1000_2 <- data.frame(random_1000_2, stringsAsFactors = FALSE)

write.csv(random_1000_2, 'random_1000_2.csv', row.names=FALSE)


