type 'a heap = {t : 'a array; mutable n : int};;

let rec monte h e i =
  if i!=0 then
    begin
      let pere = if i mod 2 = 0 then (i-2)/2 else (i-1)/2 in
      let aux = h.(pere) in
      h.(pere)<-h.(i);
      h.(i) <- aux;
      monte h e pere;
    end;;

let insertion (h:'a heap) (e:'a) =
  h.n <- h.n + 1;
  if (Array.length h.t) <= (h.n) then failwith "Pas assez de place dans le tas  !";
  h.t.(h.n) <- e;
  monte h.t e h.n;;

let rec descend t i n =
  let (f1, f2) = (i*2+1, i*2+2) in
  if f1 > n then () else
    begin
      let i_min = if f2 >= n || t.(f2) >= t.(f1) then f1 else f2 in
      if t.(i) > t.(i_min) then
        begin
          
          let aux = t.(i) in
          t.(i) <- t.(i_min);
          t.(i_min) <- aux;
        end;
    end;;

let retire (h:'a heap) =

  let res = h.t.(0) in
  h.n <- h.n - 1;
  h.t.(0) <- h.t.(h.n);
  descend h.t 0 h.n;
  res;;

let show h =
  print_string "(";
  for i=0 to h.n-1 do
    Printf.printf "%d;" h.t.(i)
  done;
  print_string ")";;

let show_t t = 
  let n = Array.length t in
  for i=0 to n-1 do
    Printf.printf "%d;" t.(i)
  done;;

let h1 = {t= Array.make 5 0; n=0};;
insertion h1 5;
show_t h1.t;;
show h1;;

insertion h1 6;;
insertion h1 4;;
show h1;;

print_int (retire h1);
show h1;;
print_int (retire h1);
show h1;
