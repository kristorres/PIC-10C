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
      T& operator[](const size_t& k);
      void push_back(const size_t& val);
      void swap(DirectedGraph& rhs);
      
      // Accessors
      T at(const size_t& k) const;
      bool empty() const;
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
    *
    * @author Kris Torres
    */
   template<typename T>
   class DirectedGraph<T>::Node final
   {
   public:
      
      // Constructor
      explicit Node(const T& weight);
      
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
      
      /** The starting node index of this directed edge. */
      size_t head_;
      
      /** The ending node index of this directed edge. */
      size_t tail_;
   };
   
   // Directed graph output operators
   template<typename T>
   std::ostream& operator<<(std::ostream& out, const DirectedGraph<T>& rhs);
   std::ostream& operator<<(std::ostream& out,
      const DirectedGraph<std::string>& rhs);
}

#endif   // PIC_10C_DIRECTED_GRAPH_H_