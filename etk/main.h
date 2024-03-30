/** @mainpage Lightning fast Event and FSM Toolkit
 *
 * This is all about an open-ended high performing Events and FSM toolkit 
 * in C++20. I have used this approach since the 80's and started refine is
 * when C++11 provided constexpr, for compile-time hashes. The idea is to
 * provide a super fast, compact solution for event-driven programming,
 * is a way that can be adopted at many different levels.
 *
 * @see Modules
 */

/** @defgroup CORE Events ans simplistic FSM
 *
 * @brief Single thread and bare-metal friendly core ...
 *
 * Here we build the foundation with POD-data events, typified with
 * a 32-bit constant hash that can be generated at compile-time. With 
 * this as a base we can construct high-performing queues, dispatchers
 * and state-machines. 
 *
 * This core is reused and enhanced on higher levels, if you actually need 
 * it.
 *
 *
 */


/** @defgroup MT MultiThreaded
 *
 * @brief Enhancements for multi-threaded solutions
 *
 * Based on the core-parts, we add features for interaction between threads
 * and scaling up the solution.
 */


/** @defgroup DIST Distributed
 *
 * @brief Enhancements for distributed solutions
 */