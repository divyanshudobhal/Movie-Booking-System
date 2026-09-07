
# 🎬 Movie Ticket Booking System

A **C++ based Movie Ticket Booking System** designed and implemented to understand and apply **Object-Oriented Programming (OOP)** and **System Design** principles.

The project focuses not only on writing the code, but on going through the complete design process — from identifying requirements and entities to designing relationships, UML diagrams, booking flows, payment flows, and finally implementing the system in C++.

---

## 📌 Project Overview

The system simulates a simplified movie ticket booking workflow where a customer can:

- View movies and shows
- Select seats
- Check seat availability
- Book tickets
- Make payments
- Receive a generated ticket
- Cancel confirmed bookings
- Release seats after cancellation or failed payment

The main goal of this project was to understand **how a real-world problem can be broken down into well-defined classes and responsibilities.**

---

## 🧠 System Design Approach

Before implementing the system, I worked through the design in multiple stages:

1. Requirements identification
2. Noun-verb analysis
3. Entity identification
4. Responsibilities of each entity
5. Class relationships
6. UML class diagram
7. Sequence diagram
8. Booking flow
9. Payment flow
10. Edge-case analysis
11. OOP and SOLID mapping
12. C++ implementation

The design materials are available in the [`docs`](./docs) directory.

---

## 🏗️ Core Classes

The system is divided into multiple classes, each responsible for a specific part of the booking workflow.

| Class | Responsibility |
|---|---|
| `Movie` | Stores movie information |
| `Cinema` | Represents the cinema |
| `Screen` | Represents a screen within a cinema |
| `Seat` | Represents an individual seat |
| `Show` | Represents a movie show |
| `ShowSeat` | Maintains seat status for a particular show |
| `Customer` | Represents the customer |
| `Booking` | Maintains booking information and status |
| `BookingService` | Orchestrates the booking workflow |
| `Payment` | Abstract payment interface |
| `UPIPayment` | Handles UPI payment |
| `CardPayment` | Handles card payment |
| `CashPayment` | Handles cash payment |
| `PriceCalculator` | Calculates total booking amount |
| `TicketPrinter` | Generates/prints ticket details |

---

## 💺 The `ShowSeat` Concept

One of the important design decisions in this project is the separation between `Seat` and `ShowSeat`.

A physical seat does not have one permanent booking status.

For example:

```text
Screen 1
 ├── Seat 1
 ├── Seat 2
 └── Seat 3

Show A → Seat 1 BOOKED
Show B → Seat 1 AVAILABLE
````

Therefore:

```text
Seat
  ↓
Physical seat

ShowSeat
  ↓
Seat + Show-specific availability
```

`ShowSeat` maintains whether a seat is **AVAILABLE** or **BOOKED** for a particular show. This prevents the seat's status from being incorrectly treated as global.

---

## 🎟️ Booking Flow

```text
Customer
    ↓
Select Show
    ↓
Select Seats
    ↓
Validate Seats
    ↓
Book Selected Seats
    ↓
Calculate Price
    ↓
Make Payment
    ↓
Payment Successful?
   /        \
 YES        NO
  ↓          ↓
Confirm    Release Seats
Booking      ↓
  ↓        Booking Failed
Print Ticket
```

The `BookingService` is responsible for coordinating this process.

It validates duplicate seats, verifies that seats exist and are available, books the selected seats, calculates the total, processes payment, and releases seats if payment fails.

---

## ❌ Cancellation Flow

```text
Confirmed Booking
       ↓
Cancel Booking
       ↓
Release Seats
       ↓
Booking Status → CANCELLED
```

Only confirmed bookings can be cancelled.

When a confirmed booking is cancelled, its associated `ShowSeat` objects are released back to the available state.

---

## 💳 Payment System

The project uses an abstract `Payment` type with different payment implementations:

```text
             Payment
                │
       ┌────────┼────────┐
       ↓        ↓        ↓
   UPI Payment  Card    Cash
              Payment  Payment
```

This allows different payment methods to be used without tightly coupling the booking logic to a particular payment implementation.

---

## 🧩 OOP Concepts Used

The project demonstrates several core OOP concepts:

### Encapsulation

Objects control their internal state through methods rather than allowing unrestricted modification.

For example, `ShowSeat` changes its status through:

```cpp
bookSeat()
releaseSeat()
```

rather than directly exposing the status.

### Abstraction

The `Payment` abstraction allows the booking system to work with different payment methods.

### Polymorphism

Different payment implementations can provide their own payment behavior.

### Composition & Aggregation

The project also demonstrates relationships such as:

* `Booking` → `Payment`
* `Booking` → `ShowSeat`
* `Show` → `ShowSeat`

---

## 🧱 SOLID Principles

The design attempts to apply SOLID principles where appropriate.

### S — Single Responsibility Principle

Responsibilities are separated between classes.

For example:

```text
BookingService     → Booking workflow
PriceCalculator    → Price calculation
TicketPrinter      → Ticket generation
Booking            → Booking state
```

### O — Open/Closed Principle

Payment implementations can be extended without changing the core booking workflow.

### L — Liskov Substitution Principle

Different payment implementations can be used through the common payment abstraction.

### I — Interface Segregation Principle

Responsibilities are kept focused rather than creating unnecessarily large interfaces.

### D — Dependency Inversion Principle

`BookingService` works with the abstract `Payment` type rather than directly depending on UPI, Card, or Cash payment classes.

---

## ⚠️ Edge Cases Considered

The system handles several common booking scenarios:

* No seats selected
* Duplicate seat selection
* Invalid/non-existent seat
* Already booked seat
* Failed payment
* Releasing seats after failed payment
* Cancelling a booking
* Attempting to cancel a non-confirmed booking

---

## 📂 Project Structure

```text
Movie-Booking-System/
│
├── Booking.cpp
├── BookingService.cpp
├── CardPayment.cpp
├── CashPayment.cpp
├── Cinema.cpp
├── Customer.cpp
├── MainMenu.cpp
├── Movie.cpp
├── Payment.cpp
├── PaymentType.cpp
├── PriceCalculator.cpp
├── Screen.cpp
├── Seat.cpp
├── Show.cpp
├── ShowSeat.cpp
├── TicketPrinter.cpp
├── UpiPayment.cpp
├── main.cpp
│
└── docs/
    ├── OOPS_used.png
    ├── class_diagram.jpg
    ├── class_relationship.jpg
    ├── noun_verb.png
    ├── sequence_diagram.jpg
    ├── sequence_diagram.svg
    └── solid_mapping.png
```

---

## 🛠️ Tech Stack

* **Language:** C++
* **Concepts:** OOP, SOLID, UML, System Design
* **Memory Management:** Smart pointers
* **Data Structures:** `vector`, `set`
* **Design Artifacts:** Class Diagram, Sequence Diagram, Relationship Mapping, Noun-Verb Analysis

---

## ▶️ How to Run

### 1. Clone the repository

```bash
git clone https://github.com/divyanshudobhal/Movie-Booking-System.git
```

### 2. Navigate to the project

```bash
cd Movie-Booking-System
```

### 3. Compile

Using g++:

```bash
g++ main.cpp -o movie_booking
```

### 4. Run

On Windows:

```bash
movie_booking.exe
```

On Linux/macOS:

```bash
./movie_booking
```

> Make sure a C++ compiler such as `g++` is installed on your system.

---

## 📚 Design Documentation

The `docs` folder contains the design work behind the implementation:

* 📊 Class Diagram
* 🔗 Class Relationships
* 🔄 Sequence Diagram
* 🔤 Noun-Verb Analysis
* 🧩 OOP Analysis
* 🏗️ SOLID Mapping

These documents show how the system was designed before translating the design into C++ code.

---

## 🎯 Learning Outcomes

This project helped me understand that **System Design is not just about drawing diagrams or writing classes.**

The important part is understanding:

* What problem are we solving?
* What entities exist?
* What responsibility belongs to each entity?
* How should the entities interact?
* What happens when something fails?
* How can the design remain maintainable?
* Why should one class be responsible for one particular concern?

The `ShowSeat` design was one of the key concepts that helped me understand how real-world state can depend on context.

---

## 🚧 Limitations

This is a **simplified learning implementation** and is not intended to represent a production-scale movie booking platform.

A real-world system would additionally need concepts such as:

* Database persistence
* Authentication and authorization
* Concurrency control
* Distributed systems
* Seat locking with expiration
* Transaction management
* Distributed payment processing
* Caching
* Message queues
* High availability
* Horizontal scaling
* Monitoring and logging
* Fault tolerance

---

## 🔮 Future Improvements

Possible future extensions include:

* [ ] Database integration
* [ ] Persistent booking history
* [ ] User authentication
* [ ] Temporary seat locking
* [ ] Payment gateway integration
* [ ] Improved exception handling
* [ ] Automated unit testing
* [ ] REST API
* [ ] Web-based frontend
* [ ] Concurrency handling
* [ ] Scalable backend architecture

---

## 👨‍💻 Author

**Divyanshu Dobhal**

Built as a learning project to explore **System Design, Object-Oriented Programming, and SOLID principles using C++.**

---

## ⭐ Feedback

If you have suggestions regarding the **architecture, class responsibilities, design patterns, OOP implementation, or overall system design**, feel free to open an issue or share your feedback.

**Designed → Implemented → Tested → Learned 🚀**
