##########################################
#For genrating random graph network file.
#Hua created.
#2016-9-23.
##########################################

require ( "igraph" )

#Plot the data read from graph file.
graph.plot <- function(links){
  net <- graph_from_data_frame( d=links, directed=T)
  plot(net, vertex.size=30, vertex.label.cex=2)
  
  return (NULL)
}

#Read the graph file, return the inside data. An option to plot or not plot by specifying plot parameter.
graph.from.file <- function(input.file, plot=TRUE){
  ##
  links <- read.table(input.file, header = FALSE, sep = '\t', quote = "", stringsAsFactors = FALSE)
  colnames(links) <- c("from", "to", "weight")
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

  dists <- runif(number.of.edges, min=0, max=10000)
  
  links <- data.frame(from = parent.nodes, to = child.nodes, dist = dists)
  write.table(links, output.file, append = FALSE, sep = '\t', quote = FALSE, row.names = FALSE, col.names = FALSE)
}

#random.graph(20000, 1000000, "graphs/20k_1m.txt")
#random.graph(40000, 1000000, "graphs/40k_1m.txt")
#random.graph(60000, 1000000, "graphs/60k_1m.txt")
#random.graph(80000, 1000000, "graphs/80k_1m.txt")
#random.graph(100000, 1000000, "graphs/100k_1m.txt")

#random.graph(50000, 200000, "graphs/50k_200k.txt")
#random.graph(50000, 400000, "graphs/50k_400k.txt")
#random.graph(50000, 600000, "graphs/50k_600k.txt")
#random.graph(50000, 800000, "graphs/50k_800k.txt")
#random.graph(50000, 1000000, "graphs/50k_1m.txt")

graph.from.file("graphs/u_a.txt")
#graph.from.file("graphs/d_cc.txt")
#graph.from.file("graphs/d_c.txt")
#graph.from.file("graphs/u_a.txt")
#graph.from.file("graphs/u_c.txt")


