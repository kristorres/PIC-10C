/**
 * Declarations and definitions of the
 * <code>Kris_Torres_UCLA_PIC_10C_Winter_2014</code> namespace,
 * <code>DirectedGraph</code> class, and <code>operator<<</code> for the
 * <code>DirectedGraph</code> class.
 *
 * @file DirectedGraph.h
 *
 * @author Kris Torres
 *
 * @date 2015-01-01
 *
 * @version 1.0
 */

#ifndef PIC_10C_DIRECTED_GRAPH_H_
#define PIC_10C_DIRECTED_GRAPH_H_

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <initializer_list>

/**
 * The <code>Kris_Torres_UCLA_PIC_10C_Winter_2014</code> namespace contains the
 * <code>DirectedGraph</code> class and <code>operator<<</code> for the
 * <code>DirectedGraph</code> class.
 */
namespace Kris_Torres_UCLA_PIC_10C_Winter_2014
{
   /**
    * In mathematics, and more specifically in graph theory,
    * <b>directed graphs</b> are collections of nodes connected by edges, where
    * the edges have a direction associated with them.
    *
    * @param T   the type of the elements
    *
    * @author Kris Torres
    */
   template<typename T>
   class DirectedGraph
   {
   public:
      
      // Class
      class Iterator;
      
      // Constructors
      DirectedGraph();
      explicit DirectedGraph(const size_t& n);
      DirectedGraph(const size_t& n, const T& val);
      DirectedGraph(const std::vector<T>& v);
      DirectedGraph(const std::initializer_list<T> il);
      DirectedGraph(const DirectedGraph& rhs);
      DirectedGraph(DirectedGraph&& rhs);
      
      // Assignment operators
      DirectedGraph& operator=(const DirectedGraph& rhs);
      DirectedGraph& operator=(DirectedGraph&& rhs);
      
      // Destructor
      virtual ~DirectedGraph();
      
      // Mutators
      T& at(const size_t& k);
      Iterator begin();
      void clear();
      void connect(const size_t& from, const size_t& to);
      void disconnect(const size_t& k);
      void disconnect(const size_t& from, const size_t& to);
      void erase(const size_t& k);
      T& front();
      T& operator[](const size_t& k);
      void push_back(const T& val);
      void swap(DirectedGraph& rhs);
      
      // Accessors
      T at(const size_t& k) const;
      bool empty() const;
      T front() const;
      size_t indegree(const size_t& k) const;
      T operator[](const size_t& k) const;
      size_t outdegree(const size_t& k) const;
      bool simple() const;
      size_t size() const;
      
      // Relational operators
      bool operator==(const DirectedGraph& rhs) const;
      bool operator!=(const DirectedGraph& rhs) const;
      
   private:
      
      // Classes
      class Node;
      class DirectedEdge;
      
      // Accessor
      void test_index(const size_t& k, const std::string& error) const;
      
      /**
       * The vector buffer into which the nodes in this directed graph are
       * stored.
       */
      std::vector<std::shared_ptr<Node>> buffer_;
      
      /**
       * The vector buffer into which the directed edges in this directed graph
       * are stored.
       */
      std::vector<DirectedGraph> path_;
   };
   
   /**
    * <i>Iterators</i> are objects that point to some nodes in a directed graph
    * and have the ability to traverse through the nodes in that directed graph.
    *
    * @author Kris Torres
    */
   template<typename T>
   class DirectedGraph<T>::Iterator
   {
   public:
      
      // Constructor
      Iterator();
      
      // Destructor
      virtual ~Iterator();
      
      // Mutators
      void next(const size_t& k);
      T& operator*();
      
      // Accessors
      T operator*() const;
      T* operator->() const;
      size_t outdegree() const;
      
      // Relational operators
      bool operator==(const Iterator& rhs) const;
      bool operator!=(const Iterator& rhs) const;
      
      // Friend
      friend class DirectedGraph<T>;
      
   private:
      
      /** The position of this iterator in the directed graph. */
      std::shared_ptr<Node> position_;
      
      /** The directed graph that this iterator traverses. */
      DirectedGraph<T>* container_;
   };
   
   /**
    * In mathematics, and more specifically in graph theory, <b>nodes</b> are
    * the fundamental units of which graphs are formed. In a diagram of a graph,
    * nodes are labeled with extra information that enables it to be
    * distinguished from other nodes.
    */
   template<typename T>
   class DirectedGraph<T>::Node final
   {
   public:
      
      // Constructor
      explicit Node(const T& val);
      
      // Destructor
      ~Node();
      
      // Friends
      friend class DirectedGraph<T>;
      friend class DirectedGraph<T>::Iterator;
      
   private:
      
      /** The data of this node in the directed graph. */
      T data_;
      
      /** The tail endpoints adjacent to this node. */
      std::vector<std::weak_ptr<Node>> next_;
   };
   
   /**
    * <b>Directed edges</b> in a directed graph are defined in terms of ordered
    * pairs of nodes.
    */
   template<typename T>
   class DirectedGraph<T>::DirectedEdge final
   {
   public:
      
      // Constructor
      DirectedEdge(const size_t& head, const size_t& tail);
      
      // Accessors
      size_t head() const;
      size_t tail() const;
      
      // Relational operators
      bool operator==(const DirectedEdge& rhs) const;
      bool operator<(const DirectedEdge& rhs) const;
      
   private:
      
      /** The position of the starting node for this directed edge. */
      size_t head_;
      
      /** The position of the ending node for this directed edge. */
      size_t tail_;
   };
   
   // Directed graph output operator
   template<typename T>
   std::ostream& operator<<(std::ostream& out, const DirectedGraph<T>& rhs);
   
   /** Constructs an empty directed graph, with no nodes. */
   template<typename T>
   inline DirectedGraph<T>::DirectedGraph() {}
   
   /**
    * Constructs a directed graph with <i>n</i> nodes. Each node has the
    * default value of the specified type for the directed graph.
    *
    * @param n   the initial number of nodes
    */
   template<typename T>
   DirectedGraph<T>::DirectedGraph(const size_t& n)
   {
      for (size_t i = 0; i < n; i++) push_back(T());
   }
   
   /**
    * Constructs a directed graph with <i>n</i> nodes. Each node has the
    * specified value.
    *
    * @param n     the initial number of nodes
    * @param val   the value of each node
    */
   template<typename T>
   DirectedGraph<T>::DirectedGraph(const size_t& n, const T& val)
   {
      for (size_t i = 0; i < n; i++) push_back(val);
   }
   
   /**
    * Constructs a directed graph that contains nodes with each of the elements
    * in the specified vector.
    *
    * @param v   the vector of elements
    */
   template<typename T>
   DirectedGraph<T>::DirectedGraph(const std::vector<T>& v)
   {
      for (const auto& element : v) push_back(element);
   }
   
   /**
    * Constructs a directed graph that contains nodes with each of the elements
    * in the specified initializer list.
    *
    * @param il   the initializer list of elements
    */
   template<typename T>
   DirectedGraph<T>::DirectedGraph(const std::initializer_list<T> il)
   {
      for (const auto& element : il) push_back(element);
   }
   
   /**
    * Constructs a directed graph with a copy of each of the nodes in the
    * specified directed graph.
    *
    * @param rhs   the directed graph to be copied
    */
   template<typename T>
   DirectedGraph<T>::DirectedGraph(const DirectedGraph& rhs) : path_(rhs.path_)
   {
      for (const auto& element : rhs.buffer_)
         buffer_.push_back(std::make_shared<Node>(element -> data_));
      
      for (const auto& element : path_)
         buffer_[element.head()] -> next_.push_back(buffer_[element.tail()]);
   }
   
   /**
    * Constructs a directed graph that acquires the nodes in the specified
    * directed graph. Note that the specified directed graph is left in an
    * unspecified but valid state.
    *
    * @param rhs   the directed graph to be moved
    */
   template<typename T>
   DirectedGraph<T>::DirectedGraph(DirectedGraph&& rhs)
      : buffer_(std::move(rhs.buffer_)), path_(rhs.path_) {}
   
   /**
    * Copies all the nodes in the specified directed graph into this directed
    * graph, with the former preserving its contents.
    *
    * @param rhs   the directed graph to be copied
    *
    * @return this directed graph after the assignment
    */
   template<typename T>
   DirectedGraph<T>& DirectedGraph<T>::operator=(const DirectedGraph& rhs)
   {
      // Tests for self-assignment.
      if (this != &rhs)
      {
         clear();
         path_ = rhs.path_;
         
         for (const auto& element : rhs.buffer_)
            buffer_.push_back(std::make_shared<Node>(element -> data_));
         
         for (const auto& element : path_)
            buffer_[element.head()] -> next_.push_back(buffer_[element.tail()]);
      }
      
      return *this;
   }
   
   /**
    * Moves all the nodes in the specified directed graph into this directed
    * graph, with the former left in an unspecified but valid state.
    *
    * @param rhs   the directed graph to be moved
    *
    * @return this directed graph after the assignment
    */
   template<typename T>
   DirectedGraph<T>& DirectedGraph<T>::operator=(DirectedGraph&& rhs)
   {
      // Tests for self-assignment.
      if (this != &rhs)
      {
         clear();
         buffer_ = std::move(rhs.buffer_);
         path_ = rhs.path_;
      }
      
      return *this;
   }
   
   /** Destroys this directed graph. */
   template<typename T>
   inline DirectedGraph<T>::~DirectedGraph() {}
   
   /**
    * Returns a reference to the value of the node at position <i>k</i> in this
    * directed graph.<p>
    *
    * The function automatically checks whether <i>k</i> is within the bounds of
    * valid positions in the directed graph, throwing an
    * <code>std::out_of_range</code> exception if it is not (i.e., if <i>k</i>
    * is greater than or equal to the number of nodes in the directed graph).
    * This is in contrast with member <code>operator[]</code>, which does not
    * check against bounds.
    *
    * @param k   the position of the node
    *
    * @return a reference to the value of the node at position <i>k</i>
    *
    * @throws std::out_of_range   if <i>k</i> is out of bounds
    */
   template<typename T>
   T& DirectedGraph<T>::at(const size_t& k)
   {
      // Tests if k is valid.
      test_index(k, "Invalid node index in directed graph: ");
      
      return buffer_[k] -> data_;
   }
   
   /**
    * Returns an iterator pointing to the first node in this directed graph.
    *
    * @return an iterator pointing to the first node
    *
    * @throws std::out_of_range   if this directed graph is empty
    */
   template<typename T>
   typename DirectedGraph<T>::Iterator DirectedGraph<T>::begin()
   {
      // Tests if the directed graph is empty.
      if (empty()) throw std::logic_error("Empty directed graph");
      
      Iterator start;
      start.position_ = buffer_.front();
      start.container_ = this;
      return start;
   }
   
   /**
    * Removes all nodes from this directed graph, leaving the directed graph
    * with no nodes.
    */
   template<typename T>
   void DirectedGraph<T>::clear()
   {
      // Removes all the directed edges.
      for (size_t i = 0; i < size(); i++) disconnect(i);
      
      buffer_.clear();
   }
   
   /**
    * Connects a directed edge from the specified starting node to the specified
    * ending node in this directed graph.<p>
    *
    * The function automatically checks whether <code>from</code> and
    * <code>to</code> are greater than or equal to the number of nodes in the
    * directed graph, throwing an <code>std::out_of_range</code> exception if it
    * is not.
    *
    * @param from   the position of the starting node
    * @param to     the position of the ending node
    *
    * @throws std::out_of_range   if either <code>from</code> or <code>to</code>
    * is out of bounds
    */
   template<typename T>
   void DirectedGraph<T>::connect(const size_t& from, const size_t& to)
   {
      // Tests if the starting and ending node indices are valid.
      test_index(from, "Invalid starting node index in directed graph: ");
      test_index(to, "Invalid ending node index in directed graph: ");
      
      buffer_[from] -> next_.push_back(buffer_[to]);
      path_.push_back(DirectedEdge(from, to));
      std::stable_sort(path_.begin(), path_.end());
   }
   
   /**
    * Disconnects all head nodes and all tail nodes adjacent to the node at
    * position <i>k</i> in this directed graph.<p>
    *
    * The function automatically checks whether <i>k</i> is greater than or
    * equal to the number of nodes in the directed graph, throwing an
    * <code>std::out_of_range</code> exception if it is not.
    *
    * @param k   the position of the node
    *
    * @throws std::out_of_range   if <i>k</i> is out of bounds
    */
   template<typename T>
   void DirectedGraph<T>::disconnect(const size_t& k)
   {
      // Tests if k is valid.
      test_index(k, "Invalid node index in directed graph: ");
      
      buffer_[k] -> next_.clear();
      
      // Removes all the directed edges whose ending node is the given node.
      for (auto& element : buffer_)
      {
         std::vector<std::weak_ptr<Node>>& edge = element -> next_;
         
         for (auto pos = edge.begin(); pos != edge.end(); pos++)
            if (pos -> lock() == buffer_[k]) { edge.erase(pos); pos--; }
      }
      
      auto test = [&](const DirectedEdge& e)
      {
         return e.head() == k || e.tail() == k;
      };
      
      path_.erase(std::remove_if(path_.begin(), path_.end(), test),
         path_.end());
   }
   
   /**
    * Disconnects a directed edge from the specified starting node to the
    * specified ending node in this directed graph.<p>
    *
    * The function automatically checks whether <code>from</code> and
    * <code>to</code> are greater than or equal to the number of nodes in the
    * directed graph, throwing an <code>std::out_of_range</code> exception if it
    * is not.
    *
    * @param from   the position of the starting node
    * @param to     the position of the ending node
    *
    * @throws std::out_of_range   if either <code>from</code> or <code>to</code>
    * is out of bounds
    */
   template<typename T>
   void DirectedGraph<T>::disconnect(const size_t& from, const size_t& to)
   {
      // Tests if the starting and ending node indices are valid.
      test_index(from, "Invalid starting node index in directed graph: ");
      test_index(to, "Invalid ending node index in directed graph: ");
      
      // Removes the rightmost occurrence of the given directed edge.
      std::vector<std::weak_ptr<Node>>& edge = buffer_[from] -> next_;
      
      for (size_t i = edge.size(); i > 0; i--)
      {
         if (edge[i - 1].lock() == buffer_[to])
         {
            edge.erase(edge.begin() + i - 1);
            break;
         }
      }
      
      for (size_t i = path_.size(); i > 0; i--)
      {
         if (path_[i - 1] == DirectedEdge(from, to))
         {
            path_.erase(path_.begin() + i - 1);
            return;
         }
      }
   }
   
   /**
    * Removes the node at position <i>k</i> from this directed graph.<p>
    *
    * The function automatically checks whether <i>k</i> is greater than or
    * equal to the number of nodes in the directed graph, throwing an
    * <code>std::out_of_range</code> exception if it is not.
    *
    * @param k   the position of the node
    *
    * @throws std::out_of_range   if <i>k</i> is out of bounds
    */
   template<typename T>
   void DirectedGraph<T>::erase(const size_t& k)
   {
      // Tests if k is valid.
      test_index(k, "Invalid node index in directed graph: ");
      
      disconnect(k);
      buffer_.erase(buffer_.begin() + k);
   }
   
   /**
    * Returns a reference to the value of the first node in this directed graph.
    *
    * @return a reference to the value of the first node
    *
    * @throws std::out_of_range   if this directed graph is empty
    */
   template<typename T>
   T& DirectedGraph<T>::front()
   {
      // Tests if the directed graph is empty.
      if (empty()) throw std::logic_error("Empty directed graph");
      
      return buffer_.front() -> data_;
   }
   
   /**
    * Returns a reference to the value of the node at position <i>k</i> in this
    * directed graph.
    *
    * @param k   the position of the node
    *
    * @return a reference to the value of the node at position <i>k</i>
    */
   template<typename T>
   inline T& DirectedGraph<T>::operator[](const size_t& k)
   {
      return buffer_[k] -> data_;
   }
   
   /**
    * Adds a node with the specified value to this directed graph, after its
    * current last node.
    *
    * @param val   the value of the new node
    */
   template<typename T>
   inline void DirectedGraph<T>::push_back(const T& val)
   {
      buffer_.push_back(std::make_shared<Node>(val));
   }
   
   /**
    * Exchanges the content of this directed graph with the content of the
    * specified directed graph.
    *
    * @param rhs   the directed graph to be swapped
    */
   template<typename T>
   void DirectedGraph<T>::swap(DirectedGraph<T>& rhs)
   {
      DirectedGraph<T> chs = *this;
      *this = rhs;
      rhs = chs;
   }
   
   /**
    * Returns the value of the node at position <i>k</i> in this directed
    * graph.<p>
    *
    * The function automatically checks whether <i>k</i> is within the bounds of
    * valid positions in the directed graph, throwing an
    * <code>std::out_of_range</code> exception if it is not (i.e., if <i>k</i>
    * is greater than or equal to the number of nodes in the directed graph).
    * This is in contrast with member <code>operator[]</code>, which does not
    * check against bounds.
    *
    * @param k   the position of the node
    *
    * @return the value of the node at position <i>k</i>
    *
    * @throws std::out_of_range   if <i>k</i> is out of bounds
    */
   template<typename T>
   T DirectedGraph<T>::at(const size_t& k) const
   {
      // Tests if k is valid.
      test_index(k, "Invalid node index in directed graph: ");
      
      return buffer_[k] -> data_;
   }
   
   /**
    * Tests if this directed graph is empty (i.e., if the directed graph
    * contains no nodes).
    *
    * @return <code>true</code> if this directed graph is empty, or
    * <code>false</code> otherwise
    */
   template<typename T>
   inline bool DirectedGraph<T>::empty() const { return buffer_.empty(); }
   
   /**
    * Returns the value of the first node in this directed graph.
    *
    * @return the value of the first node
    *
    * @throws std::out_of_range   if this directed graph is empty
    */
   template<typename T>
   T DirectedGraph<T>::front() const
   {
      // Tests if the directed graph is empty.
      if (empty()) throw std::logic_error("Empty directed graph");
      
      return buffer_.front() -> data_;
   }
   
   /**
    * Returns the <b>indegree</b> of the node at position <i>k</i> in this
    * directed graph (i.e., the number of head nodes adjacent to the node at
    * position <i>k</i>).<p>
    *
    * The function automatically checks whether <i>k</i> is greater than or
    * equal to the number of nodes in the directed graph, throwing an
    * <code>std::out_of_range</code> exception if it is not.
    *
    * @param k   the position of the node
    *
    * @return the indegree
    *
    * @throws std::out_of_range   if <i>k</i> is out of bounds
    */
   template<typename T>
   size_t DirectedGraph<T>::indegree(const size_t& k) const
   {
      // Tests if k is valid.
      test_index(k, "Invalid node index in directed graph: ");
      
      size_t head = 0;
      
      // Counts the number of head nodes adjacent to the given node.
      for (const auto& row : buffer_)
      {
         for (const auto& column : row -> next_)
            if (column.lock() == buffer_[k]) head++;
      }
      
      return head;
   }
   
   /**
    * Returns the value of the node at position <i>k</i> in this directed graph.
    *
    * @param k   the position of the node
    *
    * @return the value of the node at position <i>k</i>
    */
   template<typename T>
   inline T DirectedGraph<T>::operator[](const size_t& k) const
   {
      return buffer_[k] -> data_;
   }
   
   /**
    * Returns the <b>outdegree</b> of the node at position <i>k</i> in this
    * directed graph (i.e., the number of tail nodes adjacent to the node at
    * position <i>k</i>).<p>
    *
    * The function automatically checks whether <i>k</i> is greater than or
    * equal to the number of nodes in the directed graph, throwing an
    * <code>std::out_of_range</code> exception if it is not.
    *
    * @param k   the position of the node
    *
    * @return the outdegree
    *
    * @throws std::out_of_range   if <i>k</i> is out of bounds
    */
   template<typename T>
   size_t DirectedGraph<T>::outdegree(const size_t& k) const
   {
      // Tests if k is valid.
      test_index(k, "Invalid node index in directed graph: ");
      
      return buffer_[k] -> next_.size();
   }
   
   /**
    * Tests if this directed graph is simple, that is, if the directed graph has
    * no loops and no multiple directed edges (edges with the same starting and
    * ending nodes).
    *
    * @return <code>true</code> if this directed graph is simple, or
    * <code>false</code> otherwise
    */
   template<typename T>
   bool DirectedGraph<T>::simple() const
   {
      for (auto i = buffer_.begin(); i != buffer_.end(); i++)
      {
         std::vector<std::weak_ptr<Node>>& edge = (*i) -> next_;
         
         for (auto j = edge.begin(); j != edge.end(); j++)
         {
            // Tests if a node has a loop.
            if (*i == j -> lock()) return false;
            
            // Tests if this directed graph has multiple directed edges.
            for (auto k = edge.begin(); k != edge.end(); k++)
               if (j != k && j -> lock() == k -> lock()) return false;
         }
      }
      
      return true;
   }
   
   /**
    * Returns the number of nodes in this directed graph.
    *
    * @return the number of nodes
    */
   template<typename T>
   inline size_t DirectedGraph<T>::size() const { return buffer_.size(); }
   
   /**
    * Tests if this directed graph and the specified directed graph are equal.
    *
    * @param rhs   the directed graph to compare with this directed graph
    *
    * @return <code>true</code> if this directed graph and the specified
    * directed graph are equal, or <code>false</code> otherwise
    */
   template<typename T>
   bool DirectedGraph<T>::operator==(const DirectedGraph& rhs) const
   {
      // Tests if the two directed graphs have the same number of nodes.
      if (size() != rhs.size()) return false;
      
      // Tests if the two directed graphs have the same nodes.
      for (size_t i = 0; i < size(); i++)
         if (buffer_[i] -> data_ != rhs.buffer_[i] -> data_) return false;
      
      // Tests if the two directed graphs have the same directed edges.
      if (path_ != rhs.path_) return false;
      
      return true;
   }
   
   /**
    * Tests if this directed graph and the specified directed graph are unequal.
    *
    * @param rhs   the directed graph to compare with this directed graph
    *
    * @return <code>true</code> if this directed graph and the specified
    * directed graph are unequal, or <code>false</code> otherwise
    */
   template<typename T>
   bool DirectedGraph<T>::operator!=(const DirectedGraph& rhs) const
   {
      // Tests if the two directed graphs have the same number of nodes.
      if (size() != rhs.size()) return true;
      
      // Tests if the two directed graphs have the same nodes.
      for (size_t i = 0; i < size(); i++)
         if (buffer_[i] -> data_ != rhs.buffer_[i] -> data_) return true;
      
      // Tests if the two directed graphs have the same directed edges.
      if (path_ != rhs.path_) return true;
      
      return false;
   }
}

#endif   // PIC_10C_DIRECTED_GRAPH_H_