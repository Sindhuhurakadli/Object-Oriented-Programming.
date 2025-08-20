# Object-Oriented-Programming.
A modular e-commerce simulation showcasing OOP concepts like inheritance, polymorphism, abstraction, and exception handling. Perfect for learning and extending into a full shopping platform.

This project is a simulation of an online shopping platform developed using Object-Oriented Programming (OOP) in C++. It demonstrates the application of core OOP principles such as inheritance, polymorphism, abstraction, and exception handling to model a real-world e-commerce system.

The system begins with a User base class, extended into Buyer and Seller. Sellers can manage products by adding, deleting, and listing them, while Buyers can maintain wishlists, manage a shopping cart, and place orders. The Product class represents items with attributes like ID, name, price, and stock, along with methods for discount application and stock updates.

A Wishlist and Cart help buyers organize their shopping, while the Order class records order details such as products, quantity, and total price. Payments are handled through an abstract Payment class, with OnlinePayment and OfflinePayment implementations providing refund, status update, and detail retrieval functionalities. Buyers can also provide feedback through the Review class, which supports submitting, updating, and deleting reviews.

Custom Exception handling ensures reliable and error-free execution. The main function ties everything together by simulating seller operations, buyer shopping activities, order placement, payment processing, and product reviews.

This project provides a modular and scalable foundation for building a complete e-commerce application.
