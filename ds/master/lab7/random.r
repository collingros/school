##########################################
#For genrating random graph network file.
#Hua created.
#2016-9-23.
##########################################

require ( "igraph" )

#Plot the data read from graph file.
graph.plot <- function(links){
  net <- graph_from_data_frame( d=links, directed=T )
  plot(net, vertex.size=30, vertex.label.cex=2)
  
  return (NULL)
}

#Read the graph file, return the inside data. An option to plot or not plot by specifying plot parameter.
graph.from.file <- function(input.file, plot=TRUE){
  ##
  links <- read.table(input.file, header = FALSE, sep = '\t', quote = "", stringsAsFactors = FALSE)
  colnames(links) <- c("from", "to")
  ##
  if(plot){
    graph.plot(links)
  }
  
  return (links)
}

#Compare the two graph from two files. For small examples, use plot=TRUE; for the big one, use plot=FALSE.
graph.compare <- function(file1, file2, plot=TRUE){
  g1 <- graph.from.file(file1, plot=FALSE)
  g2 <- graph.from.file(file2, plot=FALSE)
  
  g1 <- g1[order(g1[,1], g1[,2]),]
  g2 <- g2[order(g2[,1], g2[,2]),]
  
  print(g1)
  print(g2)
  
  test <- TRUE
  test <- test & (nrow(g1) == nrow(g2)) & (ncol(g1) == ncol(g2))
  test <- test & (sum(g1 == g2) == nrow(g1) * ncol(g1))
  
  if(!test){
    stop("Sorry, not equal!")
  }else{
    #message("Congratulations!")
    if(plot){
      graph.plot(g1)
      graph.plot(g2)
    }
  }
  
  return (test)
}

#Randomly generate big graph file.
random.graph <- function(number.of.nodes = 5, number.of.edges = 10, output.file = "in_test_big.txt"){
  nodes <- paste("N", seq(from=1, to=number.of.nodes), sep="")
  
  parent.nodes <- c(nodes, nodes[sample(c(1:number.of.nodes), number.of.edges-number.of.nodes, TRUE)])
  parent.nodes <- parent.nodes[sample(c(1:length(parent.nodes)), length(parent.nodes), FALSE)]
  
  child.nodes <- c(nodes, nodes[sample(c(1:number.of.nodes), number.of.edges-number.of.nodes, TRUE)])
  child.nodes <- child.nodes[sample(c(1:length(child.nodes)), length(child.nodes), FALSE)]
  
  links <- data.frame(from = parent.nodes, to = child.nodes)
  write.table(links, output.file, append = FALSE, sep = '\t', quote = FALSE, row.names = FALSE, col.names = FALSE)
}


#graph.from.file("~/Documents/school_small/cs372/lab7/graphs/un_ac_2.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\dir\\dir_ac_2.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\dir\\dir_ac_3.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\dir\\dir_c_1.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\dir\\dir_c_2.txt")

#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\undir\\un_ac_1.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\undir\\un_ac_2.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\undir\\un_ac_3.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\undir\\un_c_1.txt")
#graph.from.file("C:\\Users\\collin\\Desktop\\school_small\\lab6\\graphs\\undir\\un_c_2.txt")


#random.graph(50000, 2000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_nodes/big_1.txt")
#random.graph(100000, 2000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_nodes/big_2.txt")
#random.graph(150000, 2000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_nodes/big_3.txt")
#random.graph(200000, 2000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_nodes/big_4.txt")


random.graph(100000, 5000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_edges/big_1.txt")
random.graph(100000, 10000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_edges/big_2.txt")
random.graph(100000, 15000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_edges/big_3.txt")
random.graph(100000, 20000000, "/home/ugrad20/cgros/Documents/school_small/cs372/lab7/graphs/func_edges/big_4.txt")
