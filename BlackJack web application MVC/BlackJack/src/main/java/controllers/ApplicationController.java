/**
 * Copyright (C) 2013 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package controllers;

import models.Card;
import models.Game;
import models.Player;
import ninja.Context;
import ninja.Result;
import ninja.Results;

import com.google.inject.Singleton;
import ninja.params.PathParam;


@Singleton
public class ApplicationController {

    public Result index() {
        return Results.html();
    }

    public Result Blackjack() {
        return Results.html().template("views/Blackjack/Blackjack.flt.html");
    }
    
    public Result gameGet(){
        Game g = new Game();
        g.newGame();
        return Results.json().render(g);
    }

    public Result newGame(Context context, Game g) {
        g.newGame();
        return Results.json().render(g);
    }

    public Result split(Context context, Game g) {
        if(context.getRequestPath().contains("split")){
            g.p.split(g);
        }
        return Results.json().render(g);
    }

    public Result stay(Context context, Game g) {
        if(context.getRequestPath().contains("stay")){
            g.p.stay(g);
        }
        return Results.json().render(g);
    }

    public Result doubleDown1(Context context, Game g) {
        g.p.doubleDown(1, g);
        return Results.json().render(g);
    }

    public Result doubleDown2(Context context, Game g) {
        g.p.doubleDown(2, g);
        return Results.json().render(g);
    }

    public Result hit11(Context context, Game g) {

        if (context.getRequestPath().contains("hit")) {
            g.hit(1);
        }
        return Results.json().render(g);
    }
    public Result hit22(Context context, Game g) {

        if (context.getRequestPath().contains("hit")) {
            g.hit(2);
        }
        return Results.json().render(g);
    }
/*
    public Result removeCard(Context context, @PathParam("column") int colNumber, Game g){
        g.remove(colNumber);
        return  Results.json().render(g);
    }
*/
   public Result moveCard(Context context, @PathParam("columnFrom") int colFrom, @PathParam("columnTo") int colTo, Game g) {
        g.move(colFrom, colTo);
        return Results.json().render(g);
    }
}



