open Thread;;

type thread_args =
  {sum : int ref; graph : int list array; parity : bool}
  
let xor a b =
  (a || b) && not (a && b);;
  
let thread thread_args =
  let {sum = p; graph = g; parity = parity} = thread_args in
  Array.iter (fun l -> 
      begin
        let d = List.length l in
        if xor (d mod 2 = 0) (parity) (*si parity = true, calcul les impairs, donc d ne doit pas être pair*)
        then p := !p+d;
      end)
    g;; 
  
let compte_graphe (g:int list array) =
  let p = ref 0 in
  let t1 = Thread.create thread {sum = p; graph = g; parity = true} in
  Thread.join t1;
  let t2 = Thread.create thread {sum = p; graph = g; parity = false} in
  
  Thread.join t2;
  !p;;


let g = [| 
  [2];
  [4];
  [0; 3];
  [2];
  [1]
|];; (*n=5*) (*nombre d’aretes : m=3*)
print_int (compte_graphe g);
