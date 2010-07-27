//===> Description ===>
//
// Driver for an advection example, integrated with corner transport
// upwind (CTU).
//
// The spatial dimension is a parameter defined in grid_base_defs.chpl.
//
//<=== Description <===


use advection_ctu_defs;


def main {
  //==== Advection velocity ====
  //-------------------------------
  // velocity = (1, 3/4, 5/8, ...)
  //-------------------------------
  var velocity: dimension*real;
  [d in dimensions] velocity(d) = 0.5 + 0.5**d;



  //===> Initialize grid ===>
  var x_low, x_high:          dimension*real,
      i_low:                  dimension*int,
      n_cells, n_ghost_cells: dimension*int;

  var N: int;
  if dimension<3 then N=100;
  else N = 50;

  for d in dimensions do {
    x_low(d)         = -1.0;
    x_high(d)        = 1.0;
    i_low(d)         = 0;
    n_cells(d)       = N;
    n_ghost_cells(d) = 2;
  }

  var G = new RectangularGrid(x_low         = x_low,
			      x_high        = x_high,
			      i_low         = i_low,
			      n_cells       = n_cells, 
			      n_ghost_cells = n_ghost_cells);
  //<=== Initialize grid <===



  //===> Initialize boundary conditions ===>
  var boundary_manager = new PeriodicBoundaryConditions(grid = G);
  //<=== Initialize boundary conditions <===



  //===> Initialize solution ===>
  def initial_condition ( x: dimension*real ) {
    var f: real = 1.0;
    for d in dimensions do
    	f *= exp(-30*x(d)**2);
    return f;
  }

  var q = G.make_grid_function(initial_condition);
  q.boundary_manager = boundary_manager;
  //<=== Initialize  solution <===



  //===> Initialize output ===>
  var time_initial: real = 0.0,
    time_final:     real = 2.0,
    n_output:       int  = 20,
    output_times:   [1..n_output] real,
    dt_output:      real = (time_final - time_initial) / n_output,
    frame_number:   int = 0;

  for i in output_times.domain do
    output_times(i) = time_initial + i * dt_output;
  //<=== Initialize output <===



  //===> Generate output ===>
  //---- Initial time ----
  q.time = time_initial;
  G.clawpack_output(q, frame_number);

  //---- Subsequent times ----
  for output_time in output_times do {
    //---- Advance q to output time ----
    G.advance_advection_ctu(q, velocity, output_time);

    //---- Write output to file ----
    frame_number += 1;
    writeln("Writing frame ", frame_number, ".");
    G.claw_output(q, frame_number);
  }
  //<=== Generate output <===
  

} // end main