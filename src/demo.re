let x = Js.Date.make ();

x |> Js.Date.toISOString;

/*let data = Dom.Storage.getItem "lol" Dom.Storage.localStorage;

  Js.log (
    switch data {
    | None => "nic nie ma!"
    | Some str => str
    }
  );*/
let data = [|1, 2, 3, 4|];

Js.(
  data |> Array.filter (fun x => x mod 2 === 0) |> Array.map (fun x => x * x) |>
  Array.reduce (fun x y => x + y) 0 |> Js.log
);
