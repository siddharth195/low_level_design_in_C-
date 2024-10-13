The Singleton design pattern is a creational pattern that ensures a class has only one instance and provides a global point of access to that instance. This is useful when exactly one object is needed to coordinate actions across the system.

Key Concepts
Single Instance: Ensures that only one instance of the class exists.
Global Access: Provides a global point of access to the instance.
Lazy Initialization: The instance is created only when it is needed.

A logging service is a common requirement in many applications to record events, errors, and other information. Logging typically needs to be globally accessible and often shouldn't be instantiated multiple times to avoid redundant resources or conflicting states. The Singleton pattern is an excellent fit for such a scenario.

