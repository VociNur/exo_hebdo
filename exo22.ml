
let classe_max (l: ('a * int) list) : int=
  List.fold_left (fun x (a, c) -> max x c) 0 l;;

let shannon (l : ('a * int) list) : float =
  let n = classe_max l +1 in
  print_int n;
  let r = Array.make n 0. in
  
  List.iter (fun (a, i) -> r.(i) <- 1. +. r.(i)) l;
  let len = Float.of_int (List.length l) in
  let res = ref 0. in
  Array.iter (fun i -> res := !res -. ((i /. len) *. Float.log (i /. len))) r;
  !res;;


let t = [(0, 0); (0, 1); (0, 2); (0, 0); (0, 2)];;
let t2 = [(0, 0); (0, 0)];;

let _ = shannon t;;
let _ = shannon t2;;
