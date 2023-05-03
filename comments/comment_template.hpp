# include <Queue>
# include <iostream>
# include <string>

// Struct representing a student in the queue
  struct QueueNode {
    // Name of the student
    std::string name;

    // Next student in the queue, nullptr if this is the last student
    QueueNode* next;
  };

  // Constructor for the queue
  // Initializes private variables to default values
  Queue();

  // Delete copy constructor + copy assignment operator
  Queue(const Queue& rhs) = delete;
  Queue& operator=(const Queue& rhs) = delete;

  // Getter for size_
  //
  // @return the number of students in the queue
  size_t GetSize() const;

  // Checks whether the queue is empty or not
  //
  // @return true if queue is empty, false otherwise
  bool IsEmpty() const;

  // Gets the first student in the queue
  //
  // @return pointer to the first student in the queue
  QueueNode* Front() const;

  // Adds a student to the end of the queue
  //
  // @param name the name of the new student
  void EnqueueStudent(const std::string& name);

  // Removes a student from the queue
  //
  // @param name the name of the student to be removed
  void RemoveStudent(const std::string& name);

  // Destructor for the queue
  // Deletes all dynamically allocated nodes in the list
  ~Queue();

  // Overloaded output operator for pretty printing
  //
  // @param os the ostream to which the contents should be printed
  // @param q the queue whose contents are to be printed
  // @return the ostream to which the contents are printed
  friend std::ostream& operator<<(std::ostream& os, const Queue& q);

private:
  // The number of students in the queue
  size_t size_;

  // Pointer to the first student in the queue, nullptr if no students
  QueueNode* head_;
};